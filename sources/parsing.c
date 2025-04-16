/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:59:28 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/16 15:25:48 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parsing.h"

/* Counts file lines and map lines (map_h) */
void	count_lines(char *filename, t_data *data)
{
	int		i;
	char	*line;
	int		fd;
	
	fd = get_fd(filename, data);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (i >= MAX_LINES - 1)
		{
			error_message("File has too many lines", 0);
			if (line)
				free(line); // free previous allocated lines
			line = NULL;
			close(fd);
			exit_game(data, EXIT_FAILURE);
		}
		if (is_map_line(line))
			data->map_data->map_h++;
		free(line);
		i++;
	}
	close(fd);
	data->map_data->file_len = i;
	#if DEBUG
	printf("File line count: %d\n", data->map_data->file_len);
	printf("Map height: %d\n", data->map_data->map_h);
	#endif
}

// get map configuration:
// colours and character position
static void	get_config(char *filename, t_data *data)
{
	int		y;
	char	*line;
	int		fd;
	//int		config_count;
	
	fd = get_fd(filename, data);
	y = 0;
	//config_count = 0;
	while (y < data->map_data->file_len  && (line = get_next_line(fd)) != NULL)
	{
		process_config_line(line, data);
		free(line);
		y++;
	}
	close (fd);
	//parse_config(data);
	#if DEBUG
	//printf("Map len in get_config function: %d\n", data->map_data->map_h);
	if (data->map_data->no_texture)
		printf("NO texture      --> [%s]\n", data->map_data->no_texture);
	if (data->map_data->so_texture)
		printf("SO texture      --> [%s]\n", data->map_data->so_texture);
	if (data->map_data->we_texture)
		printf("WE texture      --> [%s]\n", data->map_data->we_texture);
	if (data->map_data->ea_texture)
		printf("EA texture      --> [%s]\n", data->map_data->ea_texture);
	if (data->map_data->floor_colour > -1)
		printf("Floor colour    --> [0x%08X]\n", data->map_data->floor_colour);
	if (data->map_data->ceiling_colour > -1)
		printf("Ceiling colour  --> [0x%08X]\n", data->map_data->ceiling_colour);
	#endif
}

// Copy map WITHOUT checking for errors till the end of the file.
// Once the first line starting with 1 is found, all next lines are copied
void	get_map(char *filename, t_data *data)
{
	int		y;
	char	*line;
	bool	in_map;
	int		fd;
	//int		line_w;

	in_map = false;
	//line_w = 0;
	if (!(allocate_map_grid(data)))
		exit_game(data, EXIT_FAILURE);
	fd = get_fd(filename, data);
	y = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (process_line(line, &in_map, &y, data))
			continue ;
		free(line);
		close(fd);
		return ;
	}
	data->map_data->map_grid[y] = NULL;
//////////////////////////////////////////////////
	// PAD ALL MAP LINES -- shorter lines receive extra spaces at the end following the longest length.
//	https://chatgpt.com/share/67fe815b-7240-800b-83c8-85d7ce518b1b
//	1. copy all lines to a raw_map at first
//  2. and then add them to the map_grid in the struct.
	////////////////////////////////////////////////////////
	#if DEBUG
	printf("\n\n-----------EXTRACTED MAP--------------------------\n\n");
	printf("\nMap heigh: %d\n", data->map_data->map_h);
	printf("Map width: %d\n", data->map_data->map_w);
	for (int i = 0; i < y; i++)
	{
		printf("%s", data->map_data->map_grid[i]);
	}
	#endif
	close(fd);
	//parse_map(data); // if any error occurs, free all memory and exit
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
			if (ft_strchr("NSEW", c) != NULL)
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

// 1. initialises the map_data struct
// 2. get map configuration
// 3. get map structure
// 4. get initial player position and direction.
void	parse_file(char *filename, t_data *data)
{
	count_lines(filename, data);
	get_config(filename, data);
	get_map(filename, data);
	get_spawn_pos(data);
	//player_position(data);
	//close(fd); // fd is open and closed as needed
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