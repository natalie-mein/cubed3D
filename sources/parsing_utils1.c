/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:24 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/16 17:22:01 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	process_config_line(char *line, t_data *data)
{
	while (ft_iswhitespace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		data->map_data->no_texture = get_texture_path(line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		data->map_data->so_texture = get_texture_path(line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		data->map_data->we_texture = get_texture_path(line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		data->map_data->ea_texture = get_texture_path(line);
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
	fd = open("maps/valid_maps/test.cub", O_RDONLY);
	//fd = open("maps/valid_maps/test_wrong_element_num.cub", O_RDONLY);
	//fd = open("maps/valid_maps/too_many_elements.cub", O_RDONLY);
	//fd = open("maps/invalid_maps/rgb_error.cub", O_RDONLY);
	//fd = open("maps/invalid_maps/invalid_char.cub", O_RDONLY);
	//fd = open("maps/invalid_maps/two_players.cub", O_RDONLY);
	if (fd == -1)
		error_message_exit("Failed to open file", data);
	return (fd);
}

char	*get_texture_path(char *line)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line + 2, " \n");
	if (!trimmed_line)
	{
		error_message("Error\nMemory allocation failed in get_texture_path", -1);
		return (NULL);
	}
	//data->map_data->config_count++;
	return (trimmed_line);
}


