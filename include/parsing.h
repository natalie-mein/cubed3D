/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:15:42 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/17 17:24:22 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define DEBUG 0
# define MAX_LINES 50 // Figure out what is too much -------------------------------------

# define RED 0
# define GREEN 1
# define BLUE 2

# include "raycasting.h"
# include "cub3D.h"

typedef struct s_map_data
{
	int     file_len;
	char    *no_texture;
	char    *so_texture;
	char    *ea_texture;
	char    *we_texture;
	int     floor_colour;
	int     ceiling_colour;
	int		config_count;
	char    **map_grid;
	int		map_w;
	int		map_h;
} t_map_data;

typedef struct s_colour {
	int				r;
	int				g;
	int				b;
	int				colour;
}				t_colour;

void		validate_input(int argc, char *filename);
void		parse_file(char *filename, t_data *data);
void		initialise_map_data(t_data *data);
int 		get_next_number(const char *line, int *index, int colour);
//char		*get_texture_path(char *line, t_data *data);
char		*get_texture_path(char *line);
int 		get_fd(char *file_name, t_data *data);
void		count_lines(char *filename, t_data *data);
bool		is_map_line(const char *line);

bool		parse_rgb(char *trimmed_line, t_colour *colour_s);
int			create_rgb(t_colour *colour_s);
//int		get_colour(char *line, t_data *data);
int			get_colour(char *line, t_data *data);

bool		allocate_map_grid(t_data *data);
int			skip_whitespace(char *line);
bool		get_map_line(char *line, t_data *data, int y);
bool		process_line(char *line, bool *in_map, int *y, t_data *data);
void		process_config_line(char *line, t_data *data);

int			error_message(char *error_message, int code);
void		error_message_exit(char *error_message, t_data *data);

void		parse_config(t_data *data);
void		get_spawn_pos(t_data *data);

void		validate_map(t_data *data);

#endif