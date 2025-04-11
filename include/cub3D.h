/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:42:09 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/11 17:54:51 by mdahlstr         ###   ########.fr       */
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
//# include <error.h> //perror
# include <math.h> //math library
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libraries/libft/libft.h"

# define WIDTH 2048
# define HEIGHT 1024

# define SUCCESS 0
# define ERROR 1

typedef struct s_map_data
{
    int     file_len;
    char    *no_texture;
    char    *so_texture;
    char    *ea_texture;
    char    *we_texture;
    int     floor_colour;
    int     ceiling_colour;
    char    **map_grid;
	int		map_len;
	int		map_w;
	int		map_h;
} t_map_data;

typedef struct s_data
{
	t_map_data	*map_data;
	mlx_t		*mlx; // MLX pointer
	mlx_image_t	*image; // MLX window pointer
	int			player_x; //starting position of player
	int			player_y;
	char		player_dir; // cardinal direction of player start 'N', 'S', 'E', 'W'
	t_player	*player;
	t_ray		*ray;
}	t_data;

/*   errors */
void	    help_msg(void);
void	    ft_error(void);

/*   hooks   */
void	    ft_hook(void* param);

/*   map parsing   */
void	    parse_file(char *filename, t_data *data);
void		initialise_map_data(t_data *data);

/*   input validation   */
void		validate_input(int argc, char *file_name);

/*   memory management   */
void	    free_map_data(t_map_data *map_data);
#endif
