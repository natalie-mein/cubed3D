/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:42:09 by nmeintje          #+#    #+#             */
/*   Updated: 2025/05/05 16:02:15 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing.h"
# include "raycasting.h"

# include <unistd.h> //open close read write
# include <stdlib.h> //malloc free etc
# include <stdio.h> //printf
# include <sys/time.h> //gettimeofday
# include <string.h> //strerror
# include <fcntl.h>
# include <math.h> //math library
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libraries/libft/libft.h"

# define WIDTH 2048
# define HEIGHT 1024

# define SUCCESS 0
# define ERROR -1

/*  error messages  */
# define ERR_MAP_DATA "Memory allocation failure for map_data struct"
# define ERR_PIXELS "Memory allocation failure for pixels"
# define ERR_TEXTURES "Memory allocation failure for textures"
# define ERR_TEXT_BUF "Texture buffer not filled for one direction"

typedef struct s_map_data
{
	int			file_len;
	char		*no_texture;
	char		*so_texture;
	char		*ea_texture;
	char		*we_texture;
	uint32_t	floor_colour;
	uint32_t	ceiling_colour;
	bool		floor_set;
	bool		ceiling_set;
	int			config_count;
	char		**map_grid;
	int			map_w;
	int			map_h;
}	t_map_data;

typedef struct s_colour
{
	int				r;
	int				g;
	int				b;
	uint32_t		colour;
}	t_colour;

typedef struct s_render
{
	uint32_t	*text_buf[4];
	uint32_t	**pixels;
}	t_render;

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
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	start_dir;
	t_move	*move;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	screen_width;
	double	wall_x;
	double	r_dir_x;
	double	r_dir_y;
	double	r_pos_x;
	double	r_pos_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		hit;
	int		wx_top;
	int		wx_bottom;
	int		boundary;
	double	wx_distance;
	int		wx_height;
}	t_ray;

typedef struct s_text
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*floor;
	mlx_texture_t	*ceiling;
}	t_text;

typedef struct s_data
{
	t_map_data	*map_data;
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			player_x;
	int			player_y;
	char		player_dir;
	t_player	*player;
	t_ray		*ray;
	t_render	*render;
	t_text		*text;
}	t_data;

void		help_msg(void);
void		ft_error(void);
void		ft_hook(void *param);
void		validate_input(int argc, char *file_name);
void		free_data(t_data *data);
void		free_map_data(t_map_data *map_data, int height);
void		free_if_allocated(void *ptr);
void		free_2d_array(char **array, int height);

#endif
