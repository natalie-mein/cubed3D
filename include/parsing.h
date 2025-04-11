/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:15:42 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/11 17:54:09 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define DEBUG 1
# define MAX_LINES 50

typedef struct s_colour {
	int				r;
	int				g;
	int				b;
	int				colour;
}				t_colour;

/*
typedef struct s_file_data
{
	char	**file;
	int		n_lines;
	//char	**map; // data->map->matrix
	int		map_n_lines;

} t_file_data;
*/



/*   map parsing   */
//void		parse_map(char *file_name, t_game *game);

#endif