/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:16:04 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/02 15:16:06 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cubed3D.h"
//# include <math.h>

//error.h is not a library. Must delete in the main later.
// can delete later
# define MAP_WIDTH 24
# define MAP_HEIGHT 12
# define TILE_SIZE 32

extern int map[MAP_HEIGHT][MAP_WIDTH];

typedef struct s_player
{
	double  pos_x; // x pos of player
	double  pos_y; // y pos of player
	double  dir_x; // x component of player direction
	double  dir_y;  // y component of player direction
	double  plane_x; //camera plane - perpendicular to direction vector
	double  plane_y;
}   t_player;

typedef struct s_ray
{
	double  camera_x;
	double  screen_width;
	double  r_dir_x;
	double  r_dir_y;
	double  r_pos_x;
	double  r_pos_y;
	double  delta_x;
	double  delta_y;
	double  side_x;
	double  side_y;
	int     step_x;
	int     step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
}   t_ray;

typedef struct s_game
{
	char	**map;
} t_game;

//possible pointer for mlx etc
typedef struct s_data
{
	mlx_t		*mlx; // MLX pointer
	mlx_image_t	*image; // MLX window pointer
	void		*textures[5]; // MLX image pointers (on the stack)
	t_game		*map; // Map pointer (contains map details - preferably kept on the stack)
}	t_data;

void	ray_direction(t_ray *ray);
void raycast(t_player *player, t_ray *ray);
void draw_map(t_data *data, char **map);

#endif