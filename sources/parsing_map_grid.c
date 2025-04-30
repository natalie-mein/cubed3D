/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_grid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:00:32 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/30 14:03:21 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// recursive function to check for holes around the map.
static bool	is_map_closed_rec(t_data *data, bool **visited, int y, int x)
{
	if (y < 0 || y >= data->map_data->map_h
		|| x < 0 || x >= data->map_data->map_w)
		return (false);
	if (data->map_data->map_grid[y][x] == ' ')
		return (false);
	if (data->map_data->map_grid[y][x] == '1' || visited[y][x])
		return (true);
	visited[y][x] = true;
	if (!is_map_closed_rec(data, visited, y + 1, x))
		return (false);
	if (!is_map_closed_rec(data, visited, y - 1, x))
		return (false);
	if (!is_map_closed_rec(data, visited, y, x + 1))
		return (false);
	if (!is_map_closed_rec(data, visited, y, x - 1))
		return (false);
	return (true);
}

// Creates an array to keep track of visited tiles.
bool is_map_closed(t_data *data, int start_y, int start_x)
{
	int		y;
 	bool	**visited;
	bool	result;

	visited = malloc(sizeof(bool *) * data->map_data->map_h);
	if (!visited)
		return (false);
	y = 0;
	while (y < data->map_data->map_h)
	{
		visited[y] = ft_calloc(data->map_data->map_w, sizeof(bool));
		if (!visited[y])
			return (false);
		y++;
	}
	if (start_y < 0 || start_y >= data->map_data->map_h
		|| start_x < 0 || start_x >= data->map_data->map_w)
		return (false);
		
	result = is_map_closed_rec(data, visited, start_y, start_x);
	y = 0;
	while (y < data->map_data->map_h)
	{
		free(visited[y]);
		y++;
	}
	free(visited);
	return (result);
}
	