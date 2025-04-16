/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:09:36 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/16 14:19:22 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

/*void face_north(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
}

void	face_south(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 1;
	player->plane_x = -0.66;
	player->plane_y = 0;
}
void	face_east(t_player *player)
{
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
}
void	face_west(t_player *player)
{
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = -0.66;
}

void    player_direction(t_data *data)
{
	data->player->pos_x = data->player_x + 0.5; // center in the tile
	data->player->pos_y = data->player_y + 0.5;
	if (data->player_dir == 'N')
	{
		data->player->start_dir = NORTH;
		face_north(data->player);
	}
	else if (data->player_dir == 'S')
	{
		data->player->start_dir = SOUTH;
		face_south(data->player);
	}
	else if (data->player_dir == 'E')
	{
		data->player->start_dir = EAST;
		face_east(data->player);
	}   
	else if (data->player_dir == 'W')
	{
		data->player->start_dir = WEST;
		face_west(data->player);
	}
		
}*/

void    init_player(t_player *player, int start_x, int start_y, char dir)
{
	player->pos_x = start_x + 0.5; // center in the tile
	player->pos_y = start_y + 0.5;

	if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

void	draw_player(t_data *data)
{
	int pixel_x;
	int pixel_y;
	int x;
	int y;
	int size;

	pixel_x = data->player->pos_x * TILE_SIZE;
	pixel_y = data->player->pos_y * TILE_SIZE;
	size = 6;
	x = -size / 2;
	y = -size / 2;
	while (y < size)
	{
		x = -size / 2;
		while (x < size)
		{
			mlx_put_pixel(data->image, pixel_x + x, pixel_y + y, 0xFFFF00FF);
			x++;
		}
		y++;
	} 
}
