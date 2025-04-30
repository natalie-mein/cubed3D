/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_grid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/04/15 12:00:03 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/25 13:38:36 by mdahlstr         ###   ########.fr       */
=======
/*   Created: 2025/04/16 16:37:50 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/29 14:02:14 by mdahlstr         ###   ########.fr       */
>>>>>>> parsing
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

<<<<<<< HEAD
/*bool	allocate_map_grid(t_data *data)
=======
// recursive function to check for holes around the map.
static bool	is_map_closed_rec(t_data *data, bool **visited, int y, int x)
>>>>>>> parsing
{
	if (y < 0 || y >= data->map_data->map_h
		|| x < 0 || x >= data->map_data->map_w)
		return (false);
	if (data->map_data->map_grid[y][x] == ' ')
		return (false);
	if (data->map_data->map_grid[y][x] == '1' || visited[y][x])
		return (true);
	visited[y][x] = true;
	if (!is_map_closed_rec(data, visited, y + 1, x))
		return (false);
	if (!is_map_closed_rec(data, visited, y - 1, x))
		return (false);
	if (!is_map_closed_rec(data, visited, y, x + 1))
		return (false);
	if (!is_map_closed_rec(data, visited, y, x - 1))
		return (false);
	return (true);
}

// Creates an array to keep track of visited tiles.
bool is_map_closed(t_data *data, int start_y, int start_x)
{
	int		y;
 	bool	**visited;
	bool	result;

	visited = malloc(sizeof(bool *) * data->map_data->map_h);
	if (!visited)
		return (false);
	y = 0;
<<<<<<< HEAD
	data->map_data->map_grid = malloc(sizeof(char *)
		* (data->map_data->map_h + 1));
	if (!data->map_data->map_grid)
		return (error_message("Memory allocation failure for map grid", false));
	y = 0;
	while (y <= data->map_data->map_h)
=======
	while (y < data->map_data->map_h)
>>>>>>> parsing
	{
		visited[y] = ft_calloc(data->map_data->map_w, sizeof(bool));
		if (!visited[y])
			return (false);
		y++;
	}
<<<<<<< HEAD
	return (true);
}*/

bool allocate_map_grid(t_data *data)
{
    int y;

    // Allocate memory for the array of row pointers (map_h + 1 rows)
    data->map_data->map_grid = ft_calloc((data->map_data->map_h + 1), sizeof(char *));
    if (!data->map_data->map_grid)
        return (error_message("Memory allocation failure for map grid", false));

    // Allocate memory for each row in the map grid
    y = 0;
    while (y < data->map_data->map_h)
    {
        data->map_data->map_grid[y] = malloc(sizeof(char) * (data->map_data->map_w + 1));  // map_w is the width of each row
        if (!data->map_data->map_grid[y])
            return (error_message("Memory allocation failure for map row", false));
        y++;
    }
    data->map_data->map_grid[y] = NULL;  // Null-terminate the map grid (optional, depending on how you use it)

    return (true);
}

<<<<<<< HEAD

int skip_whitespace(char *line)
=======
int	skip_whitespace(char *line)
>>>>>>> 819690f (parsing improvements and a beginning of texture handling)
{
	int	x;

	x = 0;
	while (ft_iswhitespace(line[x]))
		x++;
	return (x);
}

// Copy map line into 2d grid
// Gets the longest line and sets it as map width.
bool	get_map_line(char *line, t_data *data, int y)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	data->map_data->map_grid[y] = ft_substr(line, 0, len);
	if (!data->map_data->map_grid[y])
		return (error_message("Memory allocation failure for map line", false));
	if (data->map_data->map_w < len)
		data->map_data->map_w = len;
	return (true);
}

bool	process_map_line(char *line, bool *in_map, int *y, t_data *data)
{
	int	x;

	x = skip_whitespace(line);
	if (is_map_line(line + x) || *in_map)
=======
	if (start_y < 0 || start_y >= data->map_data->map_h
		|| start_x < 0 || start_x >= data->map_data->map_w)
		return (false);
		
	result = is_map_closed_rec(data, visited, start_y, start_x);
	y = 0;
	while (y < data->map_data->map_h)
>>>>>>> parsing
	{
		free(visited[y]);
		y++;
	}
	free(visited);
	return (result);
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

<<<<<<< HEAD
	in_map = false;
	if (!(allocate_map_grid(data)))
		exit_game(data, EXIT_FAILURE);
	fd = get_fd(filename, data);
	y = 0;
	while (y < data->map_data->map_h)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (process_map_line(line, &in_map, &y, data))
			continue ;
		free(line);
		close(fd);
		return ;
	}
	data->map_data->map_grid[data->map_data->map_h] = NULL;
	#if DEBUG
	printf("\n\n-----------EXTRACTED MAP--------------------------\n\n");
	printf("\nMap heigh: %d\n", data->map_data->map_h);
	printf("Map width: %d\n", data->map_data->map_w);
	for (int i = 0; i < y; i++)
	{
		printf("%s", data->map_data->map_grid[i]);
		printf(" ----- Length: %zu\n", ft_strlen(data->map_data->map_grid[i]));
	}
	#endif
	pad_map_lines(data);
	close(fd);
}
=======

>>>>>>> parsing
