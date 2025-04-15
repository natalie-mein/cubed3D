/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:42:09 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/15 12:01:21 by mdahlstr         ###   ########.fr       */
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

/*   errors */
void	    help_msg(void);
void	    ft_error(void);

/*   hooks   */
void	    ft_hook(void* param);

/*   input validation   */
void		validate_input(int argc, char *file_name);

/*   map parsing   */
void		parse_file(char *filename, t_data *data);
void		initialise_map_data(t_data *data);
int 		get_next_number(const char *line, int *index);
char		*get_texture_path(char *line);
int 		get_fd(char *file_name, t_data *data);
void		count_file_lines(char *filename, t_data *data);
bool		is_map_line(const char *line);

int			parse_rgb(char *trimmed_line, t_colour *colour_s);
int			create_rgb(t_colour *colour_s);
int			get_colour(char *line);

bool		allocate_map_grid(t_data *data);
int			skip_whitespace(char *line);
bool		parse_map_line(char *line, int *line_w, t_data *data, int y);
bool		process_line(char *line, bool *in_map, int *y, t_data *data);


/*   memory management   */
void	    free_map_data(t_map_data *map_data);
#endif
