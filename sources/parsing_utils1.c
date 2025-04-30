/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:24 by mdahlstr          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2025/04/30 13:18:49 by mdahlstr         ###   ########.fr       */
=======
/*   Updated: 2025/04/24 18:07:15 by mdahlstr         ###   ########.fr       */
>>>>>>> a5bdf83 (test file works even with lots of spaces)
=======
/*   Updated: 2025/04/25 17:28:22 by mdahlstr         ###   ########.fr       */
>>>>>>> 819690f (parsing improvements and a beginning of texture handling)
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// Skips spaces and checks the first character of every line
// Accepted chars: N S E W F C 1, all types of spaces, newline
// and null terminator.
// Returns TRUE if a character is NOT on the list above
// Returns FALSE if the character is as expected
bool	wrong_char_in_line(char *line)
{
	int	i;
	char c;
	
	i = skip_whitespace(line);
	c = line[i];
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != 'F' && c != 'C'
		&& c != '1'&& !ft_iswhitespace(c) && c != '\n' && c != '\0')
		return (true);
	return (false);
}

void	validate_line(char *line, int fd, t_data *data)
{
	if (wrong_char_in_line(line))
	{
		#if DEBUG
		printf("in line: %s\n", line);
		#endif
		if (line)
			free(line);
		line = NULL;
		close(fd);
		error_message_exit("Wrong character found in file.", data);
	}
	if (is_map_line(line))
		data->map_data->map_h++;
	free(line);
}


/* Checks the entire file for lines starting with strange characters */
/* Counts file lines and map lines (map_h) */
void	validate_and_count_lines(char *filename, t_data *data)
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
			if (line)
				free(line);
			line = NULL;
			close(fd);
			error_message_exit("File has too many lines", data);
		}
		validate_line(line, fd, data);
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

int get_fd(char *filename, t_data *data)
{
	int	fd;

	//fd = open("maps/simple_map.cub", O_RDONLY); /////////////////////////////////////////
	//fd = open("maps/valid_maps/test.cub", O_RDONLY);
	//fd = open("maps/valid_maps/test2.cub", O_RDONLY);
	//// invalid maps: /////////////////////////////////////////////////////////
	fd = open("maps/valid_maps/test.cub", O_RDONLY);
	//fd = open("maps/valid_maps/test_zeroes.cub", O_RDONLY);
	//fd = open("maps/valid_maps/test_wrong_element_num.cub", O_RDONLY);
	//fd = open("maps/valid_maps/too_many_elements.cub", O_RDONLY);
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

	fd = open(filename, O_RDONLY);
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


