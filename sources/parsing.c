/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:59:28 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/11 17:50:11 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include "../include/parsing.h"

static int get_fd(char *file_name)
{
	int	fd;

	(void)file_name;
	fd = open("maps/simple_map.cub", O_RDONLY); /////////////////////////////////////////
	//fd = open("maps/valid_maps/test.cub", O_RDONLY);
	if (fd == -1)
		perror("Error opening file");
	return (fd);
}

void	count_file_lines(char *filename, t_data *data)
{
	int		i;
	char	*line;
	int		fd;
	
	fd = get_fd(filename);
	// handle fd error
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (i >= MAX_LINES - 1)
		{
			perror("Map file has too many lines");
			if (line)
				free(line);
			line = NULL;
			close(fd);
			break ;
		}
		free(line);
		i++;
	}
	data->map_data->map_len = i;
}


// initialise every field in map_data with zeros
void	initialise_map_data(t_data *data)
{
	data->map_data = ft_calloc(1, sizeof(t_map_data));
	if (!data->map_data)
	{
		ft_putendl_fd("Error", 2); // improve ////////////////////////////////// TO DO
		ft_putendl_fd("Memory allocation failure for map_data struct", 2);
		// free stuff
		exit(EXIT_FAILURE);
	}
}

void	parse_line(t_data *data, char *line)
{
	if (!data || !line)
	{
		// do anything else here?
		return ;
	}	
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
static void	get_config(char *filename, t_data *data)
{
	int		y;
	char	*line;
	int		fd;

	y = 0;
	fd = get_fd(filename);
	// handle fd error
	while (y < data->map_data->file_len)
	{
		//line = data->map_data->file[y]; //
		line = get_next_line(fd);
		while (ft_iswhitespace(*line)) // skip leading spaces
			line++;
		if (ft_strncmp(line, "NO", 2) == 0)
			data->map_data->no_texture = get_texture_path(line);
		if (ft_strncmp(line, "SO ", 3) == 0)
			data->map_data->so_texture = get_texture_path(line);
		if (ft_strncmp(line, "WE ", 3) == 0)
			data->map_data->we_texture = get_texture_path(line);
		if (ft_strncmp(line, "EA ", 3) == 0)
			data->map_data->ea_texture = get_texture_path(line);
		if (ft_strncmp(line, "C ", 2) == 0)
			data->map_data->ceiling_colour = get_colour(line);
		if (ft_strncmp(line, "F ", 2) == 0)
			data->map_data->floor_colour = get_colour(line);
		free(line);
		y++;
	}
	#if DEBUG
	printf("NO texture      --> [%s]\n", data->map_data->no_texture);
	printf("SO texture      --> [%s]\n", data->map_data->so_texture);
	printf("WE texture      --> [%s]\n", data->map_data->we_texture);
	printf("EA texture      --> [%s]\n", data->map_data->ea_texture);
	printf("Floor colour    --> [0x%08X]\n", data->map_data->floor_colour);
	printf("Ceiling colour  --> [0x%08X]\n", data->map_data->ceiling_colour);
	#endif
	close (fd);
}

// Copy map WITHOUT checking for errors till the end of the file.
// One the first line starting with 1 is found, all next lines are copied
void	get_map(char *filename, t_data *data)
{
	int		y;
	int		x;
	char	*line;
	int		in_map;
	int		fd;

	in_map = 0;
	#if DEBUG
	printf("\n\n-----------EXTRACTED MAP--------------------------\n\n");
	#endif
	data->map_data->map_grid = malloc(sizeof(char *) * (data->map_data->map_len + 1));
	if (!data->map_data->map_grid)
		return ; // or handle the error properly // TO DO /////////////////////////////////////
	fd = get_fd(filename);
	y = 0;
		while (y < data->map_data->map_len)
	{
		x = 0;
		line = get_next_line(fd);
		while (ft_iswhitespace(line[x]))
			x++;
		if (line[x] == '1' || in_map == 1)
		{
			in_map = 1;
			data->map_data->map_grid[y] = ft_strdup(line);
			data->map_data->map_len++;
		}
		#if DEBUG
		if (data->map_data->map_grid[y])
			printf("%s", data->map_data->map_grid[y]);
		#endif
		free(line);
		y++;
	}
	data->map_data->map_grid[data->map_data->map_len] = NULL;
	#if DEBUG
	printf("\nMap line count: %d\n", data->map_data->map_len);
	#endif
	close(fd);
}

// 1. initialises the map_data struct
// 2. get map configuration
// 3. get map structure
void	parse_file(char *filename, t_data *data)
{
	count_file_lines(filename, data); // fd closed here in case of error
	get_config(filename, data); // fd closed here in case of error
	// parse configuration(data) // if any error occurs, free all memory and exit
	get_map(filename, data); // fd closed here in case of error
	//parse_map(data); // if any error occurs, free all memory and exit
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