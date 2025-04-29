/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_validate_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:04:41 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/29 12:31:10 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// returns true if all characters in a string are spaces
static bool	only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

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
// number of players (should be 1).
void	validate_map(t_data *data)
{
	int	x;
	int	y;
	int	player_count;

	if (!data || !data->map_data || !data->map_data->map_grid)
		error_message_exit("Null pointer detected", data);
	y = 0;
	player_count = 0;
	while (y < data->map_data->map_h)
	{
		x = 0;
		while (data->map_data->map_grid[y][x])
		{
			if (!check_tile(data->map_data->map_grid[y][x], &player_count))
				error_message_exit("Invalid character detected.", data);
			x++;
		}
		if (only_spaces(data->map_data->map_grid[y]))
			error_message_exit("Empty line in map grid", data);
		y++;
	}
	if (player_count != 1)
		error_message_exit("Player count different than one.", data);
	if (!is_map_closed(data, data->player_y, data->player_x))
		error_message_exit("Map is not properly enclosed by walls.", data);
}
