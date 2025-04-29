/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_spaces_to_zeroes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:05:43 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/29 12:05:55 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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