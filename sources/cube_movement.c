/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:44:37 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/11 17:45:02 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int	is_wall(t_data *data, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(new_x + PADDING);
	map_y = (int)(new_y + PADDING);
	if (data->map_data->map_grid[map_y][map_x] == '1')
		return (1);
	map_x = (int)(new_x - PADDING);
	map_y = (int)(new_y + PADDING);
	if (data->map_data->map_grid[map_y][map_x] == '1')
		return (1);
	map_x = (int)(new_x + PADDING);
	map_y = (int)(new_y - PADDING);
	if (data->map_data->map_grid[map_y][map_x] == '1')
		return (1);
	map_x = (int)(new_x - PADDING);
	map_y = (int)(new_y - PADDING);
	if (data->map_data->map_grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

void    move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x + data->player->dir_x * MOVE_SPEED;
	new_y = data->player->pos_y + data->player->dir_y * MOVE_SPEED;
	if (!is_wall(data, new_x, new_y))
	{
		data->player->pos_x = new_x;
		data->player->pos_y = new_y;
	}
}

void    move_back(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x - data->player->dir_x * MOVE_SPEED;
	new_y = data->player->pos_y - data->player->dir_y * MOVE_SPEED;
	if (!is_wall(data, new_x, new_y))
	{
		data->player->pos_x = new_x;
		data->player->pos_y = new_y;
	}
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x - data->player->plane_x * MOVE_SPEED;
	new_y = data->player->pos_y - data->player->plane_y * MOVE_SPEED;
	if (!is_wall(data, new_x, new_y))
	{
		data->player->pos_x = new_x;
		data->player->pos_y = new_y;
	}
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x + data->player->plane_x * MOVE_SPEED;
	new_y = data->player->pos_y + data->player->plane_y * MOVE_SPEED;
	if (!is_wall(data, new_x, new_y))
	{
		data->player->pos_x = new_x;
		data->player->pos_y = new_y;
	}
}
