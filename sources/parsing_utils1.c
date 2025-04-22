/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:24 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/22 19:22:53 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// Turns all spaces in the map grid into zeroes
// [ ] -> [0]
void	spaces_to_zeroes(t_data *data)
{
	int		y;
	int		x;

	y = 0;
	while (y < data->map_data->map_h)
	{
		x = 0;
		while (data->map_data->map_grid[y][x] != '\0')
		{
			if (data->map_data->map_grid[y][x] == ' ')
				data->map_data->map_grid[y][x] = '0';
			x++;
		}
		y++;
	}
}

// Finds all lines shorter than map width and pads them with spaces.
void	pad_map_lines(t_data *data)
{
	int		y;
	char	*new_line;
	int		max_len;
	int		len;

	y = 0;
	max_len = data->map_data->map_w;
	while (y < data->map_data->map_h)
	{
		len = ft_strlen(data->map_data->map_grid[y]);
		if (len < max_len)
		{
			new_line = malloc(max_len + 1);
			if (!new_line)
			{	
				/// free previous?
				error_message_exit("Malloc failed in pad_map_lines", data);
			}
			ft_memcpy(new_line, data->map_data->map_grid[y], len);
			while (len < max_len)
				new_line[len++] = ' ';
			new_line[max_len] = '\0';
			free(data->map_data->map_grid[y]);
			data->map_data->map_grid[y] = new_line;
		}
		y++;
	}
}

void	process_config_line(char *line, t_data *data)
{
	while (ft_iswhitespace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		data->map_data->no_texture = get_texture_path(line, data);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		data->map_data->so_texture = get_texture_path(line, data);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		data->map_data->we_texture = get_texture_path(line, data);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		data->map_data->ea_texture = get_texture_path(line, data);
	else if (ft_strncmp(line, "C ", 2) == 0)
		data->map_data->ceiling_colour = get_colour(line, data);
	else if (ft_strncmp(line, "F ", 2) == 0)
		data->map_data->floor_colour = get_colour(line, data);
}

// Returns true for all lines starting wwith '1'
bool	is_map_line(const char *line)
{
	while (*line && ft_iswhitespace(*line))
		line++;
	return (*line == '1');
}

int get_fd(char *file_name, t_data *data)
{
	int	fd;

	(void)file_name;
	//fd = open("maps/simple_map.cub", O_RDONLY); /////////////////////////////////////////
	//fd = open("maps/valid_maps/test.cub", O_RDONLY);
	//fd = open("maps/valid_maps/test2.cub", O_RDONLY);

	
	//// invalid maps: /////////////////////////////////////////////////////////
	//fd = -1;
	//fd = open("maps/invalid_maps/too_few_textures.cub", O_RDONLY);
	//fd = open("maps/invalid_maps/too_few_colours.cub", O_RDONLY);
	//fd = open("maps/invalid_maps/too_many_colours.cub", O_RDONLY);
	fd = open("maps/invalid_maps/too_many_textures.cub", O_RDONLY);
	//fd = open("maps/invalid_maps/rgb_error.cub", O_RDONLY);
	//fd = open("maps/invalid_maps/invalid_char.cub", O_RDONLY);
	//fd = open("maps/invalid_maps/two_players.cub", O_RDONLY);
	//fd = open("maps/invalid_maps/open_map.cub", O_RDONLY);
	//fd = open("maps/invalid_maps/wrong_extension.xxx", O_RDONLY);
	//fd = open("maps/invalid_maps/empty_line.cub", O_RDONLY);

	if (fd == -1)
		error_message_exit("Failed to open file", data);
	return (fd);
}

// check for duplicated textures or colours.
// cleans up memory and exits in case of error
void	check_duplicated_element(t_data *data, char *line)
{
	int	x;

	x = skip_whitespace(line);
	if ((data->map_data->no_texture && line[x] == 'N')
		|| (data->map_data->so_texture && line[x] == 'S')
		|| (data->map_data->ea_texture && line[x] == 'E')
		|| (data->map_data->we_texture && line[x] == 'W')
		|| (data->map_data->ceiling_colour && line[x] == 'C')
		|| (data->map_data->floor_colour && line[x] == 'F'))
	{
		free(line);
		error_message_exit("Duplicated configuration element detected", data);
	}
}

char	*get_texture_path(char *line, t_data *data)
{
	char	*trimmed_line;

	check_duplicated_element(data, line);
	trimmed_line = ft_strtrim(line + 2, " \n");
	if (!trimmed_line)
	{
		free(line);
		error_message_exit("Memory allocation failed: get_texture_path", data);
	}
	data->map_data->config_count++;
	return (trimmed_line);
}


