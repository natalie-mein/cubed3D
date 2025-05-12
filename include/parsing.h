/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:52:37 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/05/12 12:37:48 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define DEBUG 1
# define MAX_LINES 100
# define MAX_WIDTH 200

# define RED 0
# define GREEN 1
# define BLUE 2

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include "../libraries/libft/libft.h"
# include "cub3D.h"

typedef struct s_colour	t_colour;
typedef struct s_data	t_data;

void		get_config(char *filename, t_data *data);
void		validate_input(int argc, char *filename);
void		parse_file(char *filename, t_data *data);
void		initialise_map_data(t_data *data);
int			get_fd(char *filename, t_data *data);
void		validate_and_count_lines(char *filename, t_data *data);
bool		is_map_line(const char *line);
bool		is_map_closed(t_data *data, int start_y, int start_x);
bool		parse_rgb(char *trimmed_line, t_colour *colour_s);
uint32_t	create_rgba(t_colour *colour_s);
int			get_fd(char *filename, t_data *data);
int			skip_whitespace(char *line);
void		get_map(char *filename, t_data *data);
void		pad_map_lines(t_data *data);
void		spaces_to_zeroes(t_data *data);
bool		is_right_extension(char *filename, size_t len, char *ext);
bool		has_invalid_dot_position(char *path);
void		free_map_grid(char **array, int up_to_index);
void		get_map(char *filename, t_data *data);
void		pad_map_lines(t_data *data);
void		free_map_grid(char **array, int up_to_index);
int			error_message(char *error_message, int code);
void		error_message_exit(char *error_message, t_data *data, char *str);
void		error_message_exit_no_free(char *error_message);
void		parse_config(t_data *data);
void		get_spawn_pos(t_data *data);
void		validate_map(t_data *data);
bool		only_spaces(char *str);

#endif