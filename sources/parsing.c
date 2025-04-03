/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:59:28 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/02 16:48:10 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	initialise_game(t_game *game)
{
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		ft_putendl_fd("Error\n", 2); // improve ////////////////////////////////// TO DO
		exit(EXIT_FAILURE);
	}
}

// 1. initialises the game struct
// 2. get map configuration
// 3. get map structure
void  parse_map(char *file_name, t_game *game)
{
	(void)file_name;
	
	initialise_game(game);
	// open map file (close fd on error)
	// use get next line to extract information
	
	//close fd
}

/*

1. Read the File into Memory
The map is provided in a .cub file.

The file is opened using open(), and its contents are read line by line using get_next_line() or read().

The data is stored in a structured format (e.g., an array of strings or a linked list).

2. Extract and Validate Configuration Data
Before processing the map itself, the parser first extracts configuration parameters, such as:

Textures (NO, SO, WE, EA) for walls.

Floor (F) and Ceiling (C) Colors in RGB format.

Optional parameters (if applicable to the bonus version).

Each line is checked against expected formats, and values are stored in a dedicated structure.

3. Locate the Start of the Map
The actual map (grid) starts after all configurations.

Empty lines before or after the map must be handled carefully to prevent errors.

The map is stored as a 2D array of characters, where:

'0' represents empty space.

'1' represents walls.

'N', 'S', 'E', 'W' represent the player’s starting position and direction.

Other characters might be handled depending on the bonus version (e.g., sprites, doors).

4. Validate the Map Structure
Several checks must be performed to ensure validity:

Ensure the Map is Closed

The map must be surrounded by walls (1), ensuring the player cannot escape.

Any 0 or player position on the map must be enclosed.

Only Allowed Characters Exist

The map should not contain unknown symbols.

Exactly One Player Position

The map should contain only one of N, S, E, or W.

5. Convert and Store the Map
The validated map is stored in the game’s data structure (e.g., char **map).

The player’s starting position is extracted and stored separately for initialization.

6. Handle Errors Gracefully
If any validation fails, an appropriate error message is printed (using perror() or strerror(errno), if applicable).

The program exits gracefully, freeing any allocated memory.


*/