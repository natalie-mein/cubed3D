/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:24 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/15 18:30:41 by mdahlstr         ###   ########.fr       */
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
		data->map_data->ceiling_colour = get_colour(line);
	else if (ft_strncmp(line, "F ", 2) == 0)
		data->map_data->floor_colour = get_colour(line);
}
/*
void	process_config_line(char *line, t_data *data)
{
	while (ft_iswhitespace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0 && !data->map_data->no_texture)
		data->map_data->no_texture = get_texture_path(line, data);
	else if (ft_strncmp(line, "SO ", 3) == 0 && !data->map_data->so_texture)
		data->map_data->so_texture = get_texture_path(line, data);
	else if (ft_strncmp(line, "WE ", 3) == 0 && !data->map_data->we_texture)
		data->map_data->we_texture = get_texture_path(line, data);
	else if (ft_strncmp(line, "EA ", 3) == 0 && !data->map_data->ea_texture)
		data->map_data->ea_texture = get_texture_path(line, data);
	else if (ft_strncmp(line, "C ", 2) == 0
		&& data->map_data->ceiling_colour == -1)
		data->map_data->ceiling_colour = get_colour(line, data);
	else if (ft_strncmp(line, "F ", 2) == 0
		&& data->map_data->floor_colour == -1)
		data->map_data->floor_colour = get_colour(line, data);
}
*/

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
	if (fd == -1)
	{
		error_message("Failed to open file");
		exit_game(data, EXIT_FAILURE);
	}
	return (fd);
}

char	*get_texture_path(char *line)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line + 2, " \n");
	if (!trimmed_line)
	{
		ft_putendl_fd("Error\nMemory allocation failed in get_texture_path", 2);
		return NULL;
	}
	//data->map_data->config_count++;
	return (trimmed_line);
}

// gets numbers from a string, separated by commas
int get_next_number(const char *line, int *index)
{
	int	start;
	int	num;

	start = *index;
	num = 0;
	if (line[*index] < '0' || line[*index] > '9')
		return (ERROR);
	while (line[*index] >= '0' && line[*index] <= '9')
		(*index)++;
	num = ft_atoi(&line[start]);
	while (line[*index] == ' ' || line[*index] == '\n')
		(*index)++;
	if (line[*index] != ',' && line[*index] != '\0')
		return (ERROR);
	if (line[*index] == ',')
		(*index)++;
	return (num);
}