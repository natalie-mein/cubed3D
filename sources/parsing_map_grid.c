/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_grid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:00:32 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/05/08 15:52:43 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	free_visited(bool **array, int height)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < height)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// checks for parts of the map that are not connected to the main part.
static bool	no_island(t_data *data, bool **visited)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_data->map_h)
	{
		x = 0;
		while (x < data->map_data->map_w)
		{
			if (data->map_data->map_grid[y][x] == '0' && visited[y][x] == false)
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

// recursive function to check for holes around the map.
static bool	is_map_closed_rec(t_data *data, bool **visited, int y, int x)
{
	char	c;

	if (y < 0 || y >= data->map_data->map_h
		|| x < 0 || x >= data->map_data->map_w)
		return (false);
	c = data->map_data->map_grid[y][x];
	if (c == '1' || c == ' ')
		return (true);
	if (visited[y][x])
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
bool	is_map_closed(t_data *data, int start_y, int start_x)
{
	int		y;
	bool	**visited;
	bool	result;

	result = true;
	visited = malloc(sizeof(bool *) * data->map_data->map_h);
	if (!visited)
		return (false);
	y = -1;
	while (++y < data->map_data->map_h)
	{
		visited[y] = ft_calloc(data->map_data->map_w, sizeof(bool));
		if (!visited[y])
			return (false);
	}
	if (start_y < 0 || start_y >= data->map_data->map_h
		|| start_x < 0 || start_x >= data->map_data->map_w)
		return (false);
	if (!is_map_closed_rec(data, visited, start_y, start_x))
		result = false;
	if (!no_island(data, visited))
		result = false;
	free_visited(visited, data->map_data->map_h);
	return (result);
}
