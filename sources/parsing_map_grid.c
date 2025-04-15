/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_grid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:00:03 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/15 12:01:43 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

bool	allocate_map_grid(t_data *data)
{
	int	y;

	y = 0;
	data->map_data->map_grid = malloc(sizeof(char *) * (data->map_data->map_h + 1));
	if (!data->map_data->map_grid)
	{
		ft_putendl_fd("Error\nMemory allocation failure for map grid", 2);
		return (false);
	}
	y = 0;
	while (y <= data->map_data->map_h)
	{
		data->map_data->map_grid[y] = NULL;
		y++;
	}
	return (true);
}

int skip_whitespace(char *line)
{
	int x = 0;
	while (ft_iswhitespace(line[x]))
		x++;
	return (x);
}

bool	parse_map_line(char *line, int *line_w, t_data *data, int y)
{
	data->map_data->map_grid[y] = ft_strdup(line);
	if (!data->map_data->map_grid[y])
	{
		ft_putendl_fd("Error\nMemory allocation failure for map line", 2);
		return false;
	}
	*line_w = ft_strlen(line);
	if (data->map_data->map_w < *line_w - 1)
		data->map_data->map_w = *line_w - 1;
	return (true);
}

bool	process_line(char *line, bool *in_map, int *y, t_data *data)
{
	int	x;

	x = skip_whitespace(line);
	if (is_map_line(line + x) || *in_map)
	{
		*in_map = true;
		if (!parse_map_line(line, &data->map_data->map_w, data, *y))
			return false;
		(*y)++;
	}
	free(line);
	return (true);
}