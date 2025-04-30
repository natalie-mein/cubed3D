/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parsing.h										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mdahlstr <mdahlstr@student.hive.fi>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/02 15:15:42 by mdahlstr		  #+#	#+#			 */
/*   Updated: 2025/04/22 15:54:52 by mdahlstr		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define DEBUG 1
# define MAX_LINES 50 // Figure out what is too much -------------------------------------

# define RED 0
# define GREEN 1
# define BLUE 2

# include "raycasting.h"
# include "cub3D.h"

typedef struct s_map_data
{
	int		file_len;
	char	*no_texture;
	char	*so_texture;
	char	*ea_texture;
	char	*we_texture;
	int		floor_colour;
	int		ceiling_colour;
	bool	floor_set;
	bool	ceiling_set;
	int		config_count;
	char	**map_grid;
	int		map_w;
	int		map_h;
}	t_map_data;

typedef struct s_colour {
	int				r;
	int				g;
	int				b;
	int				colour;
}				t_colour;

void		get_config(char *filename, t_data *data);


void		validate_input(int argc, char *filename);
void		parse_file(char *filename, t_data *data);
void		initialise_map_data(t_data *data);
// int 		get_next_number(const char *line, int *index, int colour); // static
//char		*get_texture_path(char *line, t_data *data);
//bool		check_duplicated_element(t_data *data, char *trimmed);

//void		parse_textures(t_data *data);


int			get_fd(char *filename, t_data *data);
void		validate_and_count_lines(char *filename, t_data *data);
bool		is_map_line(const char *line);
bool		is_map_closed(t_data *data, int start_y, int start_x);


bool		parse_rgb(char *trimmed_line, t_colour *colour_s);
int			create_rgb(t_colour *colour_s);
// int			get_colour(char *line, t_data *data);

// bool		allocate_map_grid(t_data *data); // static

// PARSING UTILS
int			get_fd(char *filename, t_data *data);
int			skip_whitespace(char *line);
//bool		get_map_line(char *line, t_data *data, int y);
void		get_map(char *filename, t_data *data);
//bool		process_map_line(char *line, bool *in_map, int *y, t_data *data);
void		pad_map_lines(t_data *data);
void		spaces_to_zeroes(t_data *data);

void		free_map_grid(char **array, int up_to_index);


//void		process_config_line(char **trimmed, t_data *data);

// bool		only_spaces(char *str); // static


// bool		get_map_line(char *line, t_data *data, int y); // static
void		get_map(char *filename, t_data *data);
// bool		process_map_line(char *line, bool *in_map, int *y, t_data *data); // static
void		pad_map_lines(t_data *data);
void		spaces_to_zeroes(t_data *data);

void		free_map_grid(char **array, int up_to_index);

// PARSING ERROR
int			error_message(char *error_message, int code);
void		error_message_exit(char *error_message, t_data *data);
void		error_message_exit_no_free(char *error_message);


void		parse_config(t_data *data);
void		get_spawn_pos(t_data *data);

void		validate_map(t_data *data);




#endif