/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:05:43 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/02 12:05:45 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
//#include "../include/cube3D.h"

// update all to use t_data instead of ray and player
void	calculate_differential(t_data *data)
{
	// perform DDA algorithm
	data->ray->hit = 0;
	while (data->ray->hit == 0)
	{
		// jump to next map square, or in a x or y direction
		if (data->ray->side_x < data->ray->side_y)
		{
			data->ray->side_x += data->ray->delta_x;
			data->ray->r_pos_x += data->ray->step_x;
			data->ray->side = 0;
		}
		else
		{
			data->ray->side_y += data->ray->delta_y;
			data->ray->r_pos_y += data->ray->step_y;
			data->ray->side = 1;
		}
		// check if ray has hit a wall
		if (data->map->matrix[(int)data->ray->r_pos_y][(int)data->ray->r_pos_x] == '1')
		{
			data->ray->hit = 1;
			break ;
		}
	}
}

void	calculate_ray_direction(t_data *data)
{
	// calculate which direction  to step and initialize side distances
	if (data->ray->r_dir_x < 0)
	{
		data->ray->step_x = -1;
		data->ray->side_x = (data->ray->r_pos_x - (int)data->ray->r_pos_x)
			* data->ray->delta_x;
	}
	else
	{
		data->ray->step_x = 1;
		data->ray->side_x = ((int) data->ray->r_pos_x + 1.0 - data->ray->r_pos_x)
			* data->ray->delta_x;
	}
	if (data->ray->r_dir_y < 0)
	{
		data->ray->step_y = -1;
		data->ray->side_y = (data->ray->r_pos_y - (int)data->ray->r_pos_y) *
			data->ray->delta_y;
	}
	else
	{
		data->ray->step_y = 1;
		data->ray->side_y = ((int)data->ray->r_pos_y + 1.0 - data->ray->r_pos_y)
			* data->ray->delta_y;
	}
}

void	calculate_ray_position(t_data *data, int x)
{
	// calculate ray position and direction
	data->ray->camera_x = 2 * x / data->ray->screen_width - 1; // x- coordinate in camera space
	data->ray->r_dir_x = data->player->dir_x + data->player->plane_x 
		* data->ray->camera_x;
	data->ray->r_dir_y = data->player->dir_y + data->player->plane_y 
		* data->ray->camera_x;

	//initialize ray position and direction in world space
	data->ray->r_pos_x = data->player->pos_x;
	data->ray->r_pos_y = data->player->pos_y;

	// calcuate step and side distances
	data->ray->delta_x = fabs(1 / data->ray->r_dir_x);
	data->ray->delta_y = fabs(1 / data->ray->r_dir_y);
}

void	calculate_wall_height(t_data *data, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	// compute distance of the ray and store it for rendering
		if (data->ray->side == 0)
			data->ray->perp_wall_dist = (data->ray->r_pos_x - data->player->pos_x
				+ (1 - data->ray->step_x) / 2) / data->ray->r_dir_x;
		else
			data->ray->perp_wall_dist = (data->ray->r_pos_y - data->player->pos_y 
				+ (1 - data->ray->step_y) / 2) / data->ray->r_dir_y;
		line_height = (int)(MAP_HEIGHT / data->ray->perp_wall_dist);
		draw_start = -line_height / 2 + MAP_HEIGHT / 2;
		draw_end = line_height / 2 + MAP_HEIGHT / 2;
		if (draw_start < 0)
    		draw_start = 0;
		if (draw_end >= MAP_HEIGHT)
    		draw_end = MAP_HEIGHT - 1;
		// draw vertical line on the image buffer
		for (int y = draw_start; y <= draw_end; y++) {
    		mlx_put_pixel(data->image, x, y, 0xFFFFFFFF); // white wall pixel
		}
}

void raycast(t_data *data) 
{
	int		x;
	
	x = 0;
	while (x < data->ray->screen_width)
	{
		calculate_ray_position(data, x);
		calculate_ray_direction(data);
		calculate_differential(data);
		calculate_wall_height(data, x);
		x++;
	}
}
