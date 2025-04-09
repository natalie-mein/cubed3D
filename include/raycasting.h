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
# define MAP_WIDTH 1000
# define MAP_HEIGHT 600
# define TILE_SIZE 50
# define MOVE_SPEED 0.05

extern int map[MAP_HEIGHT][MAP_WIDTH];

typedef enum s_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
}	t_dir;


typedef struct s_move
{
	bool	left;
	bool	right;
	bool	back;
	bool	forward;
	bool	rotate_l;
	bool	rotate_r;
}	t_move;


typedef struct s_player
{
	double  pos_x; // x pos of player
	double  pos_y; // y pos of player
	double  dir_x; // x component of player direction
	double  dir_y;  // y component of player direction
	double  plane_x; //camera plane - perpendicular to direction vector
	double  plane_y;
	int		start_dir;
	t_move	*move;
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
	char	**matrix;
} t_game;

typedef struct s_data
{
	mlx_t		*mlx; // MLX pointer
	mlx_image_t	*image; // MLX window pointer
	void		*textures[5]; // MLX image pointers (on the stack)
	int			player_x; //starting position of player
	int			player_y;
	char		player_dir; // cardinal direction of player start 'N', 'S', 'E', 'W'
	t_game		*map; // Map pointer (contains map details - preferably kept on the stack)
	t_player	*player;
	t_ray		*ray;
}	t_data;

void	raycast(t_data *data);
void	draw_map(t_data *data, char **map);
void    draw_player(t_data *data);
void    init_player(t_player *player, int start_x, int start_y, char dir);
void	key_hooks(mlx_key_data_t keydata, void *param);
void	no_key_hook(mlx_key_data_t keydata, t_data *data);

void	move_player(t_data *data);
void    move_forward(t_data *data);
void    move_back(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void    rotate_left(t_data *data);
void    rotate_right(t_data *data);
void    render_game(void *param);

int		init_data(t_data *data);
int		init_game(t_data *data);
void    exit_game(t_data *data);

#endif