/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:59:28 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/29 12:44:38 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include "parsing.h"

/// DELETE /////////////////////////////////////////////////////////////////////////////////////
void print_map(t_map_data *map_data, char *message)
{
	int i;

	i = 0;
	printf("\n\nMap in map grid - %s\n", message);
	while (i < map_data->map_h)
	{
		printf("%s", map_data->map_grid[i]);
		printf(" ---- length: %zu\n", ft_strlen(map_data->map_grid[i]));
		i++;
	}
}

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
	#if DEBUG
	print_map(data->map_data, "after padding");
	#endif
	get_spawn_pos(data);
	validate_map(data);
	spaces_to_zeroes(data);
	#if DEBUG
	print_map(data->map_data, "after validation and turning spaces to zeroes");
	#endif
}

/*


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
The validated map is stored in the map_data’s data structure (e.g., char **map).

The player’s starting position is extracted and stored separately for initialization.

6. Handle Errors Gracefully
If any validation fails, an appropriate error message is printed (using perror() or strerror(errno), if applicable).

The program exits gracefully, freeing any allocated memory.

*/