/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:05:50 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/09 13:42:38 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	validate_argc(int argc)
{
	if (argc < 2)
	{
		printf("Error\nAdd a map file.\n"); ////////////////////////// TO DO /////////
		exit(EXIT_FAILURE);
	}
	if (argc > 2)
	{
		printf("Error\nToo many arguments.\n");  ////////////////////////// TO DO /////////
		exit(EXIT_FAILURE);
	}
}

static void	validate_file_name(char *map_file_name)
{
	size_t	len;

	len = ft_strlen(map_file_name);
	if (map_file_name[len - 4] != '.' || map_file_name[len - 3] != 'c'
		|| map_file_name[len - 2] != 'u' || map_file_name[len - 1] != 'b')
	{
		printf("Error\nWrong file extension.\n");  ////////////////////////// TO DO /////////
		exit(EXIT_FAILURE);
	}
}

// Checks for number of arguments and map file extension.
// Exits without calling cleanup_game, since no memory has been allocated yet.
// Prints error messages in 3 cases:
// (1) Too few arguments, (2) too many arguments and (3) wrong file extension.
// (should be ".cub").
void	validate_input(int argc, char *map_file_name)
{
	validate_argc(argc);
	validate_file_name(map_file_name);
}