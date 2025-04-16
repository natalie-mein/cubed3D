/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_grid2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:37:50 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/16 18:20:53 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
/*
static bool is_map_closed(t_data *data, int start_y, int start_x)
{
	int y;
	int x;
	bool visited[data->map_data->map_h][data->map_data->map_w];

	if (start_y < 0 || start_y >= data->map_data->map_h
		|| start_x < 0 || start_x >= data->map_data->map_w)
		return (false);
		
	y = 0;
	// initialise the visited array to false
	while (y < data->map_data->map_h)
	{
		x = 0;
		while (x < data->map_data->map_w)
		{
			visited[x][y] = false;
			x++;
		}
		y++;
	}
	if (data->map_data->map_grid[start_y][start_x] == '1'
		|| visited[start_y][start_x])
		return (true); // Wall or already checked
	if (data->map_data->map_grid[start_y][start_x] == ' ')
		return (false); // Space outside the map

	visited[start_y][start_x] = true;
	// Recursively check all four directions
	return (is_map_closed(data, start_y + 1, start_x)
		&& is_map_closed(data, start_y - 1, start_x)
		&& is_map_closed(data, start_y, start_x + 1)
		&& is_map_closed(data, start_y, start_x - 1));
}
*/

static bool	check_valid_chars(char tile)
{
	if (tile == ' ' || tile == '1' || tile == '0'
		|| tile == 'N' || tile == 'S' || tile == 'E'
		|| tile == 'W' || tile == '\n')
		return (true);
	return (false);
}

// Checks for valid tiles
// counts the player's initial position to make sure it is 1
static bool	check_tile(char tile, int *player_count)
{
	if (!check_valid_chars(tile))
		return (false);
	if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		(*player_count)++;
	return (true);
}

// Checks for valid characters (P, E, C, 0, 1),
// walls (the map should be completely enclosed),
// number of players (should be 1),
// number of exits (should be 1).
// collectibles (should be 1 or more),
// valid path (collectibles and exit should be accessible).
void	validate_map(t_data *data)
{
	int	x;
	int	y;
	int	player_count;

	if (!data || !data->map_data || !data->map_data->map_grid)
		error_message_exit("Null pointer detected", data);
	x = 0;
	y = 0;
	player_count = 0;
	while (y < data->map_data->map_h)
	{
		x = 0;
		while (data->map_data->map_grid[y][x])
		{
			if (!check_tile(data->map_data->map_grid[y][x], &player_count))
			{
				#if DEBUG
				printf("Invalid character: [%c]\n", data->map_data->map_grid[y][x]);
				#endif
				error_message_exit("Invalid character detected.", data);
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		error_message_exit("Player count different than one.", data);
	//if (!is_map_closed(data, data->player_y, data->player_x))
	//	error_message_exit("Map is not properly enclosed by walls.", data);
}
