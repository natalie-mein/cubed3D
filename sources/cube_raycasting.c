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

#include "cubed3D.h"
#include "raycastng.h"


void raycast(t_player *player, t_ray *ray) 
{
	int		x;
	
	x = 0;
	while (x < ray->screen_width)
	{
		// calculate ray position and direction
		ray->camera_x = 2 * x / ray->screen_width - 1; // x- coordinate in camera space
		ray->r_dir_x = player->dir_x + player->plane_x * ray->camera_x;
		ray->r_dir_y = player->dir_y + player->plane_y * ray->camera_x;

		//initialize ray position and direction in world space
		ray->r_pos_x = player->pos_x;
		ray->r_pos_y = player->pos_y;

		// calcuate step and side distances
		ray->delta_x = 

		x++;
	}
	
		// Calculate step and side distances
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
		double side_dist_x, side_dist_y;

		// Initialize step and initial side distance
		int step_x, step_y;
		int hit = 0;
		int side; // 0 = vertical, 1 = horizontal

		// Calculate which direction to step and initialize side distances
		if (ray_dir_x < 0) {
			step_x = -1;
			side_dist_x = (ray_pos_x - (int)ray_pos_x) * delta_dist_x;
		} else {
			step_x = 1;
			side_dist_x = ((int)ray_pos_x + 1.0 - ray_pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0) {
			step_y = -1;
			side_dist_y = (ray_pos_y - (int)ray_pos_y) * delta_dist_y;
		} else {
			step_y = 1;
			side_dist_y = ((int)ray_pos_y + 1.0 - ray_pos_y) * delta_dist_y;
		}

		// Perform DDA algorithm
		while (hit == 0) {
			// Jump to next map square, or in x or y direction
			if (side_dist_x < side_dist_y) {
				side_dist_x += delta_dist_x;
				ray_pos_x += step_x;
				side = 0;
			} else {
				side_dist_y += delta_dist_y;
				ray_pos_y += step_y;
				side = 1;
			}

			// Check if ray has hit a wall
			if (map[(int)ray_pos_y][(int)ray_pos_x] == 1) {
				hit = 1;
			}
		}

		// Compute the distance of the ray and store it for rendering
		double perp_wall_dist;
		if (side == 0) {
			perp_wall_dist = (ray_pos_x - player->pos_x + (1 - step_x) / 2) / ray_dir_x;
		} else {
			perp_wall_dist = (ray_pos_y - player->pos_y + (1 - step_y) / 2) / ray_dir_y;
		}
	}
}


