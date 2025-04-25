/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:59:28 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/25 16:39:55 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

void	process_config_line(char **trimmed, t_data *data)
{
	if (check_duplicated_element(data, *trimmed) == true)
	{
		#if DEBUG
		printf("DUPLICATED: [%s]\n", *trimmed);
		#endif
		free(*trimmed);
		error_message_exit("Found duplicated elements (parsing_utils1 - process_config_line)", data);
	}
	else
	{
		if (ft_strncmp(*trimmed, "NO ", 3) == 0)
			data->map_data->no_texture = get_texture_path(trimmed, data);
		else if (ft_strncmp(*trimmed, "SO ", 3) == 0)
			data->map_data->so_texture = get_texture_path(trimmed, data);
		else if (ft_strncmp(*trimmed, "WE ", 3) == 0)
			data->map_data->we_texture = get_texture_path(trimmed, data);
		else if (ft_strncmp(*trimmed, "EA ", 3) == 0)
			data->map_data->ea_texture = get_texture_path(trimmed, data);
		else if (ft_strncmp(*trimmed, "C ", 2) == 0)
			data->map_data->ceiling_colour = get_colour(*trimmed, data);
		else if (ft_strncmp(*trimmed, "F ", 2) == 0)
			data->map_data->floor_colour = get_colour(*trimmed, data);
		free(*trimmed);
	}
}

// get map configuration:
// colours and character position
static void	get_config(char *filename, t_data *data)
{
	int		y;
	char	*line;
	char	*trimmed;
	int		fd;
	
	fd = get_fd(filename, data);
	y = 0;
	while (y < data->map_data->file_len)
	{	
		line = get_next_line(fd);
		if (line != NULL)
		{
			trimmed = ft_strtrim(line, " \t\n\r");
			free(line);
			if (!trimmed)
			{
				close(fd);
				error_message_exit("Failed trimming line from file", data);
			}
			process_config_line(&trimmed, data);
		}
		y++;
	}
	close (fd);
	parse_config(data);
	#if DEBUG
	printf("NO texture      --> [%s]\n", data->map_data->no_texture);
	printf("SO texture      --> [%s]\n", data->map_data->so_texture);
	printf("WE texture      --> [%s]\n", data->map_data->we_texture);
	printf("EA texture      --> [%s]\n", data->map_data->ea_texture);
	printf("Floor colour    --> [0x%08X]\n", data->map_data->floor_colour);
	printf("Ceiling colour  --> [0x%08X]\n", data->map_data->ceiling_colour);
	#endif
}

void	get_spawn_pos(t_data *data)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	x = 0;
	while (y < data->map_data->map_h)
	{
		x = 0;
		while (x < data->map_data->map_w)
		{
			c = data->map_data->map_grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				data->player_dir = c;
				data->player_y = y;
				data->player_x = x;
				#if DEBUG
				printf("Player first position: y=%d, x=%d, direction=%c\n", data->player_y, data->player_x, data->player_dir);  // problems here
				#endif
				return ;
			}
			x++;
		}
		y++;
	}
	
}
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
The validated map is stored in the map_data’s data structure (e.g., char **map).

The player’s starting position is extracted and stored separately for initialization.

6. Handle Errors Gracefully
If any validation fails, an appropriate error message is printed (using perror() or strerror(errno), if applicable).

The program exits gracefully, freeing any allocated memory.

*/