/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_spawn_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:03:47 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/05/06 12:19:31 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_spawn_pos(t_data *data)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	x = 0;
	while (y < data->map_data->map_h)
	{
		x = 0;
		while (x < data->map_data->map_w)
		{
			c = data->map_data->map_grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				data->player_dir = c;
				data->player_y = y;
				data->player_x = x;
				return ;
			}
			x++;
		}
		y++;
	}
}
