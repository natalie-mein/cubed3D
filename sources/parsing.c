/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:59:28 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/17 16:29:01 by mdahlstr         ###   ########.fr       */
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

// Finds all lines shorter than map width and pads them with spaces.
void	pad_map_lines(t_data *data)
{
	int		y;
	char	*new_line;
	int		max_len;
	int		len;

	y = 0;
	max_len = data->map_data->map_w;
	while (y < data->map_data->map_h)
	{
		len = ft_strlen(data->map_data->map_grid[y]);
		if (len < max_len)
		{
			new_line = malloc(max_len + 1);
			if (!new_line)
			{	
				/// free previous?
				error_message_exit("Malloc failed in pad_map_lines", data);
			}
			ft_memcpy(new_line, data->map_data->map_grid[y], len);
			while (len < max_len)
				new_line[len++] = ' ';
			new_line[max_len] = '\0';
			free(data->map_data->map_grid[y]);
			data->map_data->map_grid[y] = new_line;
		}
		else if (len > max_len)
			error_message("Error in map padding", ERROR); // Maybe unnecessary
		y++;
	}
}


// Copy map WITHOUT checking for errors till the end of the file.
// Once the first line starting with 1 is found, all next lines are copied
// All lines are padded according to the longest
void	get_map(char *filename, t_data *data)
{
	int		y;
	char	*line;
	bool	in_map;
	int		fd;

	in_map = false;
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
	pad_map_lines(data);
	#if DEBUG
	printf("\n\n-----------EXTRACTED MAP--------------------------\n\n");
	printf("\nMap heigh: %d\n", data->map_data->map_h);
	printf("Map width: %d\n", data->map_data->map_w);
	for (int i = 0; i < y; i++)
	{
		printf("%s\n", data->map_data->map_grid[i]);
	}
	#endif
	close(fd);
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

void print_map(t_map_data *map_data)
{
	int i;

	i = 0;
	printf("map in map grid:\n");
	while (i < map_data->map_h)
	{
		printf("%s", map_data->map_grid[i]);
		printf("length: %zu\n", ft_strlen(map_data->map_grid[i]));
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
	count_lines(filename, data);
	get_config(filename, data);
	get_map(filename, data);
	#if DEBUG
	//print_map(data->map_data); // after padding the lines, all will have the same length.
	#endif
	get_spawn_pos(data);
	validate_map(data);
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