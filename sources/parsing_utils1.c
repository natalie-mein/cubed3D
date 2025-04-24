/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:24 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/24 18:03:48 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* Counts file lines and map lines (map_h) */
void	count_lines(char *filename, t_data *data)
{
	int		i;
	char	*line;
	int		fd;
	
	fd = get_fd(filename, data);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (i >= MAX_LINES - 1)
		{
			error_message("File has too many lines", 0);
			if (line)
				free(line); // free previous allocated lines
			line = NULL;
			close(fd);
			exit_game(data, EXIT_FAILURE);
		}
		if (is_map_line(line))
			data->map_data->map_h++;
		free(line);
		i++;
	}
	close(fd);
	data->map_data->file_len = i;
	#if DEBUG
	printf("File line count: %d\n", data->map_data->file_len);
	printf("Map height: %d\n", data->map_data->map_h);
	#endif
}

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
	int		len;

	y = 0;
	while (y < data->map_data->map_h)
	{
		len = ft_strlen(data->map_data->map_grid[y]);
		if (len < data->map_data->map_w)
		{
			new_line = malloc(data->map_data->map_w + 1);
			if (!new_line)
			{	
				free_map_grid(data->map_data->map_grid, y);
				error_message_exit("Malloc failed in pad_map_lines", data);
			}
			ft_memcpy(new_line, data->map_data->map_grid[y], len);
			while (len < data->map_data->map_w)
				new_line[len++] = ' ';
			new_line[data->map_data->map_w] = '\0';
			free(data->map_data->map_grid[y]);
			data->map_data->map_grid[y] = new_line;
		}
		y++;
	}
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
	fd = open("maps/simple_map.cub", O_RDONLY); /////////////////////////////////////////
	//fd = open("maps/valid_maps/test.cub", O_RDONLY);
	//fd = open("maps/valid_maps/test2.cub", O_RDONLY);

	
	//// invalid maps: /////////////////////////////////////////////////////////
	//fd = -1;
	//fd = open("maps/invalid_maps/too_few_textures.cub", O_RDONLY);
	//fd = open("maps/invalid_maps/too_few_colours.cub", O_RDONLY);
	//fd = open("maps/invalid_maps/too_many_colours.cub", O_RDONLY);
	//fd = open("maps/invalid_maps/too_many_textures.cub", O_RDONLY);
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
// returns TRUE if a duplicated texture or colour is detected.
bool	check_duplicated_element(t_data *data, char *trimmed)
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

char	*get_texture_path(char **trimmed, t_data *data)
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


