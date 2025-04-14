/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:24 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/14 16:38:26 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int get_fd(char *file_name, t_data *data)
{
	int	fd;

	(void)file_name;
	//fd = open("maps/simple_map.cub", O_RDONLY); /////////////////////////////////////////
	fd = open("maps/valid_maps/test.cub", O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error\nFailed to open file", 2);
		exit_game(data, EXIT_FAILURE);
	}
	return (fd);
}

void	count_file_lines(char *filename, t_data *data)
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
			perror("Map file has too many lines");
			if (line)
				free(line);
			line = NULL;
			close(fd);
			break ;
		}
		free(line);
		i++;
	}
	data->map_data->file_len = i;
	#if DEBUG
	printf("File len in count_file_lines: %d\n", data->map_data->file_len);
	#endif
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