/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:52:14 by nmeintje          #+#    #+#             */
/*   Updated: 2025/05/05 13:56:02 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
0,0 = top left, HEIGHT, WIDTH = bottom right
*/
void	calculate_wall_pixels(t_player *player, t_ray *ray)
{
	int	half_win;
	int	half_wall;

	half_win = (int)(HEIGHT / 2);
	half_wall = ray->wx_height / 2;
	ray->wx_top = half_win - half_wall;
	ray->wx_bottom = half_win + half_wall;
	if (ray->wx_top < 0)
		ray->wx_top = 0;
	if (ray->wx_bottom >= HEIGHT)
		ray->wx_bottom = HEIGHT;
	if (ray->boundary == 0)
		ray->wall_x = player->pos_y + ray->wx_distance * ray->r_dir_y;
	else
		ray->wall_x = player->pos_x + ray->wx_distance * ray->r_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

int	choose_wall_texture(t_ray *ray)
{
	if (ray->r_dir_y < 0 && ray->boundary == 1)
		return (NORTH);
	if (ray->r_dir_y > 0 && ray->boundary == 1)
		return (SOUTH);
	if (ray->r_dir_x < 0 && ray->boundary == 0)
		return (WEST);
	if (ray->r_dir_x > 0 && ray->boundary == 0)
		return (EAST);
	return (ERROR);
}

int	find_location(t_ray *ray, int texture)
{
	int	x;

	x = (int)(ray->wall_x * TEXTURE);
	if (texture == NORTH || texture == EAST)
		return (x);
	if (texture == SOUTH || texture == WEST)
		return (TEXTURE - x - 1);
	return (ERROR);
}

void	render_wall_pixels(t_data *data, t_ray *ray, int x)
{
	int			i;
	int			j;
	double		k;
	double		m;
	uint32_t	color;

	i = choose_wall_texture(ray);
	j = find_location(ray, i);
	m = (double)TEXTURE / fmax(ray->wx_height, 1.0);
	k = (double)(ray->wx_top - HEIGHT / 2 + ray->wx_height / 2) * m;
	while (ray->wx_top < ray->wx_bottom)
	{
		k += m;
		color = data->render->text_buf[i][(TEXTURE * ((int)k % TEXTURE)) + j];
		if (color > 0)
			data->render->pixels[ray->wx_top][x] = color;
		ray->wx_top++;
	}
}

void	render_image(t_data *data)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;
	uint32_t	*pixels;

	color = 0;
	pixels = (uint32_t *)data->image->pixels;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (data->render->pixels[y][x] > 0)
				color = data->render->pixels[y][x];
			else if (y < HEIGHT / 2)
				color = data->map_data->ceiling_colour;
			else
				color = data->map_data->floor_colour;
			pixels[y * WIDTH + x] = color;
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}
