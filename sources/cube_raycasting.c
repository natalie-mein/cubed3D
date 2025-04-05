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

#include "../include/raycasting.h"

void	calculate_differential(t_ray *ray)
{
	// perform DDA algorithm
	ray->hit = 0;
	while (ray->hit == 0)
	{
		// jump tp next map square, or in a x or y direction
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->r_pos_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_x += ray->delta_y;
			ray->r_pos_y += ray->step_y;
			ray->side = 1;
		}
		// check if ray has hit a wall
		if (map[(int)ray->r_pos_y][(int)ray->r_pos_x] == 1)
			ray->hit = 1;
	}
}

void	ray_direction(t_ray *ray)
{
	// calculate which direction  to step and initialize side distances
	if (ray->r_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (ray->r_pos_x - (int)ray->r_pos_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = ((int) ray->r_pos_x + 1.0 - ray->r_pos_x) * ray->delta_x;
	}
	if (ray->r_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (ray->r_pos_y - (int)ray->r_pos_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = ((int) ray->r_pos_y + 1.0 - ray->r_pos_y) * ray->delta_y;
	}
}

void	ray_position(t_player *player, t_ray *ray, int x)
{
	// calculate ray position and direction
	ray->camera_x = 2 * x / ray->screen_width - 1; // x- coordinate in camera space
	ray->r_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->r_dir_y = player->dir_y + player->plane_y * ray->camera_x;

	//initialize ray position and direction in world space
	ray->r_pos_x = player->pos_x;
	ray->r_pos_y = player->pos_y;

	// calcuate step and side distances
	ray->delta_x = fabs(1 / ray->r_dir_x);
	ray->delta_y = fabs(1 / ray->r_dir_y);
}

void raycast(t_player *player, t_ray *ray) 
{
	int		x;
	
	x = 0;
	while (x < ray->screen_width)
	{
		ray_position(player, ray, x);
		ray_direction(ray);
		calculate_differential(ray);
		
		// compute distance of the ray and store it for rendering
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->r_pos_x - player->pos_x + (1 - ray->step_x) / 2) / ray->r_dir_x;
		else
			ray->perp_wall_dist = (ray->r_pos_y - player->pos_y + (1 - ray->step_y) / 2) / ray->r_dir_y;

		x++;
	}
	printf("Column: %d | Distance: %f | Wall side: %s\n", 
		x, 
		ray->perp_wall_dist, 
		ray->side == 0 ? "X (East/West)" : "Y (North/South)");
}
