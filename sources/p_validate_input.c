/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_validate_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:05:50 by nmeintje          #+#    #+#             */
/*   Updated: 2025/05/06 12:19:44 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	validate_argc(int argc)
{
	if (argc < 2)
	{
		error_message("Add a map file.", -1);
		exit(EXIT_FAILURE);
	}
	if (argc > 2)
	{
		error_message("Too many arguments.", -1);
		exit(EXIT_FAILURE);
	}
}

static void	validate_file_name(char *map_file_name)
{
	size_t	len;
	int		dot;
	int		i;

	len = ft_strlen(map_file_name);
	dot = 0;
	i = 0;
	while (map_file_name[i])
	{
		if (map_file_name[i] == '.')
		{
			dot = 1;
			break ;
		}
		i++;
	}
	if (dot == 0 || map_file_name[len - 1] == '.')
		error_message_exit_no_free("Missing file name or extension");
	if (!is_right_extension(map_file_name, len, ".cub"))
		error_message_exit_no_free("Map file has the wrong file extension.");
}

// Checks for number of arguments and map file extension.
// Exits without calling cleanup_game, since no memory has been allocated yet.
// Prints error messages in 3 cases:
// (1) Too few arguments, (2) too many arguments and (3) wrong file extension.
// (should be ".cub").
void	validate_input(int argc, char *filename)
{
	validate_argc(argc);
	validate_file_name(filename);
}
