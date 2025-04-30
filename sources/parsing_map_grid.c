/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_grid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:00:03 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/22 18:35:39 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*bool	allocate_map_grid(t_data *data)
{
	int	y;

	y = 0;
	data->map_data->map_grid = malloc(sizeof(char *) * (data->map_data->map_h + 1));
	if (!data->map_data->map_grid)
		return (error_message("Memory allocation failure for map grid", false));
	y = 0;
	while (y <= data->map_data->map_h)
	{
		data->map_data->map_grid[y] = NULL;
		y++;
	}
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


int skip_whitespace(char *line)
{
	int x;

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
	{
		*in_map = true;
		if (!get_map_line(line, data, *y))
			return (false);
		(*y)++;
	}
	free(line);
	return (true);
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
		if (process_map_line(line, &in_map, &y, data))
			continue ;
		free(line);
		close(fd);
		return ;
	}
	//data->map_data->map_grid[y] = NULL;
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
