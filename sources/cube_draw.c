/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:43:56 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/15 17:38:15 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycasting.h"

void draw_tile(t_data *data, int x, int y, uint32_t color)
{
	int i;
	int j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(data->image, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void draw_map(t_data *data, char **map)
{
	int			y;
	int			x;
	char		tile;
	uint32_t	color;

	data->map_data->map_h = 0;
	x = 0;
	y = 0;
	data->map_data->map_w = ft_strlen(map[0]);
	while (map[data->map_data->map_h] != NULL) /// SOMETHING IS WRONG HERE.
		data->map_data->map_h++;
	while (y < data->map_data->map_h)
	{
		x = 0;
		while (x < data->map_data->map_w)
		{
			tile = map[y][x];
			if (tile == '1')
				color = 0xFFFFFFFF; // white wall
			else if (tile == '0')
				color = 0x222222FF; // dark floor
			else
				color = 0xFF0000FF; // red for unknown
			draw_tile(data, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}

//Render function that includes raycasting
void render_game(void *param)
{
	t_data *data = (t_data *)param;

	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
	{
		printf("Failed to create image!\n");
		return;
	}
	draw_map(data, data->map_data->map_grid);
	move_player(data);
	draw_player(data);
	raycast(data);
	//mlx_image_to_window(data->mlx, data->image, 0, 0);
}



