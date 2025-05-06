/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:43:56 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/05/06 16:18:47 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_player(t_data *data)
{
	int	pixel_x;
	int	pixel_y;
	int	x;
	int	y;
	int	size;

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

void	clear_pixel_buffer(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			data->render->pixels[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	render_game(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	clear_pixel_buffer(data);
	move_player(data);
	raycast(data);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
		error_message_exit(ERR_IMAGE, data, NULL);
	render_image(data);
}
