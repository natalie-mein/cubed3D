/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:15:42 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/03 10:25:35 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3D.h"
# include <unistd.h> //open close read write
# include <stdlib.h> //malloc free etc
# include <stdio.h> //printf
# include <sys/time.h> //gettimeofday
# include <string.h> //strerror
# include <error.h> //perror
# include <math.h> //math library
# include "../libraries/MLX42/include/MLX42/MLX42.h"
# include "../libraries/libft/libft.h"

/*   input validation   */
void		validate_input(int argc, char *map_file_name);

/*   map parsing   */
//void		parse_map(char *file_name, t_game *game);

#endif