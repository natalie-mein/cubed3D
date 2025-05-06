/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_get_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:02:51 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/05/06 12:19:28 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Copy map line into 2d grid
// Gets the longest line and sets it as map width.
static bool	get_map_line(char *line, t_data *data, int y)
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

static bool	process_map_line(char *line, bool *in_map, int *y, t_data *data)
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

static bool	allocate_map_grid(t_data *data)
{
	int	y;

	y = 0;
	data->map_data->map_grid = malloc(sizeof(char *)
			* (data->map_data->map_h + 1));
	if (!data->map_data->map_grid)
		return (error_message("Memory allocation failure for map grid", false));
	y = 0;
	while (y <= data->map_data->map_h)
	{
		data->map_data->map_grid[y] = NULL;
		y++;
	}
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
	pad_map_lines(data);
	close(fd);
}
