/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:24 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/29 14:27:15 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// Returns true for all lines starting wwith '1'
bool	is_map_line(const char *line)
{
	while (*line && ft_iswhitespace(*line))
		line++;
	return (*line == '1');
}

void	free_map_grid(char **array, int up_to_index)
{
	int	i;

	i = 0;
	while (i < up_to_index)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	skip_whitespace(char *line)
{
	int	x;

	x = 0;
	while (ft_iswhitespace(line[x]))
		x++;
	return (x);
}

int get_fd(char *filename, t_data *data)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_message_exit("Failed to open file", data);
	return (fd);
}






