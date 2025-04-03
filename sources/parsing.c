/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:59:28 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/03 15:13:50 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <fcntl.h>   // For open() and O_RDONLY // No idea why it's not compiling without this here :(
#include "parsing.h"

// initialise every field in game with zeros
static void	initialise_game(t_game **game)
{
	*game = ft_calloc(1, sizeof(t_game));
	if (!*game)
	{
		ft_putendl_fd("Error", 2); // improve ////////////////////////////////// TO DO
		ft_putendl_fd("Memory allocation failure for game struct", 2);
		exit(EXIT_FAILURE);
	}
}

static int get_fd(char *file_name)
{
	int	fd;

	(void)file_name;
	fd = open("maps/simple_map.cub", O_RDONLY);
	if (fd == -1)
		perror("Error opening file");
	return (fd);
}

static void get_map(t_game *game, char *file_name)
{
	int		fd;
	size_t	i;
	char	*line;

	(void)file_name;
	//line = NULL;
	fd = get_fd(file_name);
	if (fd == -1)
	{
		free_game(game);
		exit(EXIT_FAILURE);
	}
	#if DEBUG
	printf("Success: FD = %d\n", fd);
	#endif
	// Allocate memory for game->map (assuming a max number of lines)
	game->map = malloc(sizeof(char *) * MAX_LINES);
	if (!game->map)
	{
		perror("Memory allocation failed");
		close(fd);
		exit(EXIT_FAILURE);
	}
	// read and store lines
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		#if DEBUG
		printf("  %s", line);
		#endif
		if (i >= MAX_LINES - 1)
		{
			perror("Map file has too many lines");
			break ;
		}
		game->map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	
	game->map[i] = NULL;
	close(fd);
}

// 1. initialises the game struct
// 2. get map configuration
// 3. get map structure
void	parse_map(char *file_name, t_game *game)
{
	(void)file_name;

	initialise_game(&game);
	get_map(game, file_name);
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