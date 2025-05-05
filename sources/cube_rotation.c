/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:05:17 by nmeintje          #+#    #+#             */
/*   Updated: 2025/05/02 13:35:17 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_left(t_data *data)
{
	t_player	*p;
	double		rot_speed;
	double		old_dir_x;
	double		old_plane_x;

	p = data->player;
	rot_speed = 0.05;
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(-rot_speed) - p->dir_y * sin(-rot_speed);
	p->dir_y = old_dir_x * sin(-rot_speed) + p->dir_y * cos(-rot_speed);
	p->plane_x = p->plane_x * cos(-rot_speed) - p->plane_y * sin(-rot_speed);
	p->plane_y = old_plane_x * sin(-rot_speed) + p->plane_y * cos(-rot_speed);
}

void	rotate_right(t_data *data)
{
	t_player	*p;
	double		rot_speed;
	double		old_dir_x;
	double		old_plane_x;

	p = data->player;
	rot_speed = 0.05;
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
	p->dir_y = old_dir_x * sin(rot_speed) + p->dir_y * cos(rot_speed);
	p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
	p->plane_y = old_plane_x * sin(rot_speed) + p->plane_y * cos(rot_speed);
}
