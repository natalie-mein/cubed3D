
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:42:09 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/15 16:54:17 by mdahlstr         ###   ########.fr       */
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

typedef struct s_data t_data;
typedef struct s_map_data t_map_data;
typedef struct s_colour t_colour;
typedef struct s_map_data t_map_data;

/*   errors */
void		help_msg(void);
void		ft_error(void);

/*   hooks   */
void		ft_hook(void* param);

/*   input validation   */
void		validate_input(int argc, char *file_name);

/*   memory management   */
void	    free_map_data(t_map_data *map_data);
void		free_if_allocated(void *ptr);

#endif
