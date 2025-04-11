/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:42:09 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/10 18:06:39 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parsing.h"
//# include <fcntl.h>
# include <unistd.h> //open close read write
# include <stdlib.h> //malloc free etc
# include <stdio.h> //printf
# include <sys/time.h> //gettimeofday
# include <string.h> //strerror
//# include <error.h> //perror
# include <math.h> //math library
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libraries/libft/libft.h"

# define WIDTH 2048
# define HEIGHT 1024

# define SUCCESS 0
# define ERROR 1

// file:
// 1 - textures
// 2 - colours
// 3 - map
typedef struct s_file_data
{
	char	**file;
	int		file_line_count;
	char	**map;
	int		map_line_count;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		ceiling_colour;
	int		floor_colour;
} t_file_data;

/*   errors */
void	help_msg(void);
void	ft_error(void);

/*   hooks   */
void	ft_hook(void* param);

/*   map parsing   */
void	parse_file(char *file_name, t_file_data *file_data);

/*   memory management   */
void	free_file_data(t_file_data *file_data);
#endif
