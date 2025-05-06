/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:59:28 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/05/06 12:19:52 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// 1. count file and map lines
// 2. get map configuration
// 3. get map structure
// 4. get initial player position and direction.
// 5. validate map 
void	parse_file(char *filename, t_data *data)
{
	validate_and_count_lines(filename, data);
	get_config(filename, data);
	get_map(filename, data);
	get_spawn_pos(data);
	validate_map(data);
	spaces_to_zeroes(data);
}
