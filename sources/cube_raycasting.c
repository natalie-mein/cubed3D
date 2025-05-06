/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:05:43 by nmeintje          #+#    #+#             */
/*   Updated: 2025/05/05 13:53:49 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
Calculates ray position and direction by: setting the ray direction for the
curent screen column and converting it into a number from -1 to 1 (l - r).
And then calculating the direcction of the ray by adjusting it based on
where the player is looking and their field of view (plane)
*/
void	calculate_ray_position(t_data *data, t_player *player, int x)
{
	data->ray->camera_x = 2 * x / data->ray->screen_width - 1;
	data->ray->r_dir_x = player->dir_x + player->plane_x * data->ray->camera_x;
	data->ray->r_dir_y = player->dir_y + player->plane_y * data->ray->camera_x;
}

/*
Calculates how far a ray has to go in x and y before crossing a gridline
Delta_x and Delta_y are used to walk through the grid evenly and step through 
squares.
The ray starts at the players position.
*/
void	calculate_delta_distance(t_player *player, t_ray *ray)
{
	ray->delta_x = fabs(1 / ray->r_dir_x);
	ray->delta_y = fabs(1 / ray->r_dir_y);
	ray->r_pos_x = player->pos_x;
	ray->r_pos_y = player->pos_y;
}

/*
Calculates which direction to step and initialize side distances
based on player position
Side_x and Side_y are the initial distances to the first X and Y sides
of the next grid cell
*/
void	calculate_ray_direction(t_player *player, t_ray *ray)
{
	if (ray->r_dir_x >= 0)
	{
		ray->step_x = 1;
		ray->side_x = ((int)ray->r_pos_x + 1.0 - player->pos_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = -1;
		ray->side_x = (player->pos_x - (int)ray->r_pos_x) * ray->delta_x;
	}
	if (ray->r_dir_y >= 0)
	{
		ray->step_y = 1;
		ray->side_y = ((int)ray->r_pos_y + 1.0 - player->pos_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = -1;
		ray->side_y = (player->pos_y - (int)ray->r_pos_y) * ray->delta_y;
	}
}

/*
Performs DDA algorithm
Wals the ray forward through the grid until the ray hits a '1' on the map
at each step, it checks whcish direction is closer X or Y and moves the cell
in that direction.
if the new position hits a wall, it breaks out of the loop
The close the wall the taller it appears. 
*/
void	calculate_differential(t_data *d, t_ray *ray)
{
	while (1)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->r_pos_x += ray->step_x;
			ray->boundary = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->r_pos_y += ray->step_y;
			ray->boundary = 1;
		}
		if (d->map_data->map_grid[(int)ray->r_pos_y][(int)ray->r_pos_x] == '1')
			break ;
	}
	if (ray->boundary == 0)
		ray->wx_distance = ray->side_x - ray->delta_x;
	else
		ray->wx_distance = ray->side_y - ray->delta_y;
	ray->wx_height = (int)(HEIGHT / ray->wx_distance);
}

/*
Starts from left most column of the screen and loops across the screen
Casts one ray per screen column. For each column is calculates where the
ray goes, how far it travels and what to draw
*/
void	raycast(t_data *data)
{
	t_ray	*ray;
	int		x;

	x = 0;
	ray = data->ray;
	while (x < ray->screen_width)
	{
		calculate_ray_position(data, data->player, x);
		calculate_delta_distance(data->player, ray);
		calculate_ray_direction(data->player, ray);
		calculate_differential(data, ray);
		calculate_wall_pixels(data->player, ray);
		render_wall_pixels(data, ray, x);
		x++;
	}
}
