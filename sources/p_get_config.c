/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:49:02 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/30 16:52:55 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// get RGB values and converts them to hex colour.
// through bitwise shift operations
static int	get_colour(char *line, t_data *data)
{
	char		*original_line;
	char		*trimmed_line;
	t_colour	colour_s;
	char		type;

	original_line = line;
	type = line[skip_whitespace(line)];
	line = line + 1;
	ft_bzero(&colour_s, sizeof(t_colour));
	trimmed_line = ft_strtrim(line, " \n");
	if (!parse_rgb(trimmed_line, &colour_s))
	{
		free(original_line);
		free(trimmed_line);
		exit_game(data, EXIT_FAILURE);
	}
	free(trimmed_line);
	colour_s.colour = create_rgba(&colour_s);
	data->map_data->config_count++;
	if (type == 'C')
		data->map_data->ceiling_set = 1;
	else if (type == 'F')
		data->map_data->floor_set = 1;
	return (colour_s.colour);
}

static char	*get_texture_path(char **trimmed, t_data *data)
{
	char	*only_path;

	if (!trimmed || !*trimmed)
		return (NULL);
	only_path = ft_strdup(*trimmed + 3);
	if (!only_path)
	{
		free(*trimmed);
		error_message_exit("Memory allocation failed: get_texture_path", data);
	}
	free(*trimmed);
	*trimmed = NULL;
	data->map_data->config_count++;
	return (only_path);
}

// check for duplicated textures or colours.
// returns TRUE if a duplicated texture or colour is detected.
static bool	check_duplicated_element(t_data *data, char *trimmed)
{
	if ((data->map_data->no_texture && trimmed[0] == 'N')
		|| (data->map_data->so_texture && trimmed[0] == 'S')
		|| (data->map_data->ea_texture && trimmed[0] == 'E')
		|| (data->map_data->we_texture && trimmed[0] == 'W')
		|| (data->map_data->ceiling_set != 0 && trimmed[0] == 'C')
		|| (data->map_data->floor_set != 0 && trimmed[0] == 'F'))
	{
		return (true);
	}
	return (false);
}

static void	process_config_line(char **trimmed, t_data *data)
{
	if (check_duplicated_element(data, *trimmed) == true)
	{
		#if DEBUG
		printf("DUPLICATED: [%s]\n", *trimmed);
		#endif
		free(*trimmed);
		error_message_exit("Found duplicated elements (parsing_utils1 - process_config_line)", data);
	}
	else
	{
		if (ft_strncmp(*trimmed, "NO ", 3) == 0)
			data->map_data->no_texture = get_texture_path(trimmed, data);
		else if (ft_strncmp(*trimmed, "SO ", 3) == 0)
			data->map_data->so_texture = get_texture_path(trimmed, data);
		else if (ft_strncmp(*trimmed, "WE ", 3) == 0)
			data->map_data->we_texture = get_texture_path(trimmed, data);
		else if (ft_strncmp(*trimmed, "EA ", 3) == 0)
			data->map_data->ea_texture = get_texture_path(trimmed, data);
		else if (ft_strncmp(*trimmed, "C ", 2) == 0)
			data->map_data->ceiling_colour = get_colour(*trimmed, data);
		else if (ft_strncmp(*trimmed, "F ", 2) == 0)
			data->map_data->floor_colour = get_colour(*trimmed, data);
		free(*trimmed);
	}
}

// get map configuration:
// colours and character position
void	get_config(char *filename, t_data *data)
{
	int		y;
	char	*line;
	char	*trimmed;
	int		fd;
	
	fd = get_fd(filename, data);
	y = 0;
	while (y < (data->map_data->file_len - data->map_data->map_h))
	{	
		line = get_next_line(fd);
		if (line != NULL)
		{
			trimmed = ft_strtrim(line, " \t\n\r");
			free(line);
			if (!trimmed)
			{
				close(fd);
				error_message_exit("Failed trimming line from file", data);
			}
			process_config_line(&trimmed, data);
		}
		y++;
	}
	close (fd);
	parse_config(data);
	#if DEBUG
	printf("NO texture      --> [%s]\n", data->map_data->no_texture);
	printf("SO texture      --> [%s]\n", data->map_data->so_texture);
	printf("WE texture      --> [%s]\n", data->map_data->we_texture);
	printf("EA texture      --> [%s]\n", data->map_data->ea_texture);
	printf("Floor colour    --> [%08x]\n", data->map_data->floor_colour);
	printf("Ceiling colour  --> [%08x]\n", data->map_data->ceiling_colour);
	#endif
}
