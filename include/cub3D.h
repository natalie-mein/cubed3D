/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:42:09 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/03 13:35:36 by mdahlstr         ###   ########.fr       */
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

// main struct:
typedef struct s_game
{
	char	**map;
} t_game;

/*   errors */
void	help_msg(void);
void	ft_error(void);

/*   hooks   */
void	ft_hook(void* param);

/*   map parsing   */
void	parse_map(char *file_name, t_game *game);

/*   memory management   */
void	free_game(t_game *game);
#endif
