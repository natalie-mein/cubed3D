/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_grid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:00:03 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/16 17:05:27 by mdahlstr         ###   ########.fr       */
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
	int x = 0;
	while (ft_iswhitespace(line[x]))
		x++;
	return (x);
}

bool	get_map_line(char *line, t_data *data, int y)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	data->map_data->map_grid[y] = ft_strdup(line);
	if (!data->map_data->map_grid[y])
		return (error_message("Memory allocation failure for map line", false));
	if (data->map_data->map_w < len)
		data->map_data->map_w = len;
	return (true);
}

bool	process_line(char *line, bool *in_map, int *y, t_data *data)
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