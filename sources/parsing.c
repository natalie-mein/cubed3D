/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:59:28 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/10 18:38:06 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <fcntl.h>   // For open() and O_RDONLY // No idea why it's not compiling without this here :(
#include "parsing.h"

static int get_fd(char *file_name)
{
	int	fd;

	(void)file_name;
	//fd = open("maps/simple_map.cub", O_RDONLY);
	fd = open("maps/valid_maps/test.cub", O_RDONLY);
	if (fd == -1)
		perror("Error opening file");
	return (fd);
}

void	count_file_lines(t_file_data *file_data, char *file_name)
{
	int		fd;
	int		i;
	char	*line;
	
	fd = get_fd(file_name);
	if (fd == -1)
	{
		free_file_data(file_data);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (i >= MAX_LINES - 1)
		{
			perror("Map file has too many lines");
			break ;
		}
		free(line);
		i++;
	}
	file_data->file_line_count = i;
	close(fd);
}


// initialise every field in file_data with zeros
static void	initialise_file_data(t_file_data **file_data)
{
	*file_data = ft_calloc(1, sizeof(t_file_data));
	if (!*file_data)
	{
		ft_putendl_fd("Error", 2); // improve ////////////////////////////////// TO DO
		ft_putendl_fd("Memory allocation failure for file_data struct", 2);
		exit(EXIT_FAILURE);
	}
}

// HERE IS WHERE THE FILE NAME IS TEMPORARILY HARDCODED ////////////////////////////////////


static void get_file(t_file_data *file_data, char *file_name)
{
	int		fd;
	int		i;
	char	*line;

	(void)file_name;
	//line = NULL;
	fd = get_fd(file_name);
	if (fd == -1)
	{
		free_file_data(file_data);
		exit(EXIT_FAILURE);
	}
	#if DEBUG
	printf("Success. File opened. FD = %d\n\n", fd);
	#endif
	// Allocate memory for file_data->map (assuming a max number of lines) // COUNT LINES FIRST?
	file_data->file = malloc(sizeof(char *) * MAX_LINES);
	if (!file_data->file)
	{
		perror("Memory allocation failed");
		close(fd);
		exit(EXIT_FAILURE);
	}
	// read and store lines
	i = 0;
	// copy_file_content(file_data->file, fd)
	#if DEBUG
	printf("\n\n---------FILE CONTENTS--------------------------\n\n");
	#endif
	while (i < file_data->file_line_count)
	{
		line = get_next_line(fd);
		#if DEBUG
		printf("%s", line);
		#endif
		file_data->file[i] = ft_strdup(line);
		free(line);
		i++;
	}
	#if DEBUG
	printf("\n\n---------PARSED DATA----------------------------\n\n");
	printf("\nFile line count: %d\n", i);
	#endif
	file_data->file[i] = NULL;
	close(fd);
}

char	*get_texture_path(char *line)
{
	char	*trimmed_line;

	line = line + 2;
	trimmed_line = ft_strtrim(line, " \n");
	return (trimmed_line);
}

// gets numbers from a string, separated by commas
int get_next_number(const char *line, int *index)
{
	int	start;
	int	num;

	start = *index;
	num = 0;
	if (line[*index] < '0' || line[*index] > '9')
		return (ERROR);
	while (line[*index] >= '0' && line[*index] <= '9')
		(*index)++;
	num = ft_atoi(&line[start]);
	while (line[*index] == ' ' || line[*index] == '\n')
		(*index)++;
	if (line[*index] != ',' && line[*index] != '\0')
		return (ERROR);
	if (line[*index] == ',')
		(*index)++;
	return (num);
}

// checks for numbers smaller than 0 and larger than 255
// checks if there are other characters after the last number
int	parse_rgb(char *trimmed_line, t_colour *colour_s)
{
	int	i;

	i = 0;
	colour_s->r = get_next_number(trimmed_line, &i);
	colour_s->g = get_next_number(trimmed_line, &i);
	colour_s->b = get_next_number(trimmed_line, &i);
	if (colour_s->r < 0 || colour_s->r > 255
		|| colour_s->g < 0 || colour_s->g > 255
		|| colour_s->b < 0 || colour_s->b > 255)
	{
		ft_putendl_fd("Error\nRGB values must be between 0 and 255", 2);
		return (0);
	}
	while (trimmed_line[i] == ' ')
		i++;
	if (trimmed_line[i] != '\0')
		return (0);
	return (1);
}

int	create_rgb(t_colour *colour_s)
{
	return (0xFFFFFF & (colour_s->r << 16 | colour_s->g << 8 | colour_s->b));
}

// get RGB values and converts them to hex colour.
// through bitwise shift operations
int	get_colour(char *line)
{
	char		*trimmed_line;
	t_colour	colour_s;

	ft_bzero(&colour_s, sizeof(t_colour));
	line = line + 1;
	trimmed_line = ft_strtrim(line, " \n");
	if (!parse_rgb(trimmed_line, &colour_s))
		printf("RGB parsing error\n");
	colour_s.colour = create_rgb(&colour_s);
	return (colour_s.colour);
}



// get map configuration:
// colours and character position
static void	get_config(t_file_data *file_data)
{
	int		y;
	char	*line;

	y = 0;
	while (y < file_data->file_line_count)
	{
		line = file_data->file[y];
		while (ft_iswhitespace(*line)) // skip leading spaces
			line++;
		if (ft_strncmp(line, "NO", 2) == 0)
			file_data->north_texture = get_texture_path(line);
		if (ft_strncmp(line, "SO ", 3) == 0)
			file_data->south_texture = get_texture_path(line);
		if (ft_strncmp(line, "WE ", 3) == 0)
			file_data->west_texture = get_texture_path(line);
		if (ft_strncmp(line, "EA ", 3) == 0)
			file_data->east_texture = get_texture_path(line);
		if (ft_strncmp(line, "C ", 2) == 0)
			file_data->ceiling_colour = get_colour(line);
		if (ft_strncmp(line, "F ", 2) == 0)
			file_data->floor_colour = get_colour(line);
		//free(line);
		y++;
	}
	#if DEBUG
	printf("NO texture      --> [%s]\n", file_data->north_texture);
	printf("SO texture      --> [%s]\n", file_data->south_texture);
	printf("WE texture      --> [%s]\n", file_data->west_texture);
	printf("EA texture      --> [%s]\n", file_data->east_texture);
	printf("Floor colour    --> [0x%08X]\n", file_data->floor_colour);
	printf("Ceiling colour  --> [0x%08X]\n", file_data->ceiling_colour);
	#endif
}

void	get_map(t_file_data	*file_data)
{
	int		y;
	int		x;
	char	*line;
	//int		map_line_count;

	y = 0;
	#if DEBUG
	printf("\n\n-----------EXTRACTED MAP--------------------------\n\n");
	#endif
	file_data->map = malloc(sizeof(char *) * (file_data->file_line_count + 1));
	if (!file_data->map)
		return ; // or handle the error properly // TO DO /////////////////////////////////////
	while (y < file_data->file_line_count)
	{
		x = 0;
		line = file_data->file[y];
		while (ft_iswhitespace(line[x]))
			x++;
		if (line[x] == '1')
		{
			file_data->map[y] = ft_strdup(line);
			file_data->map_line_count++;
		}
			#if DEBUG
		if (file_data->map[y])
			printf("%s", file_data->map[y]);
		#endif
		y++;
	}
	file_data->map[file_data->map_line_count] = NULL;
	#if DEBUG
	printf("\nMap line count: %d\n", file_data->map_line_count);
	#endif
}

// 1. initialises the file_data struct
// 2. get map configuration
// 3. get map structure
void	parse_file(char *file_name, t_file_data *file_data)
{
	(void)file_name;

	initialise_file_data(&file_data);
	count_file_lines(file_data, file_name);
	get_file(file_data, file_name); // fd is closed here
	get_config(file_data);
	// parse configuration
	get_map(file_data);
	// parse map
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
The validated map is stored in the file_data’s data structure (e.g., char **map).

The player’s starting position is extracted and stored separately for initialization.

6. Handle Errors Gracefully
If any validation fails, an appropriate error message is printed (using perror() or strerror(errno), if applicable).

The program exits gracefully, freeing any allocated memory.


*/