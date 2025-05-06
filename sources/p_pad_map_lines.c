/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_pad_map_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:23:03 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/05/06 16:27:46 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Finds all lines shorter than map width and pads them with spaces.
void	pad_map_lines(t_data *data)
{
	int		y;
	char	*new_line;
	int		len;

	y = 0;
	while (y < data->map_data->map_h)
	{
		len = ft_strlen(data->map_data->map_grid[y]);
		if (len < data->map_data->map_w)
		{
			new_line = malloc(data->map_data->map_w + 1);
			if (!new_line)
			{
				free_map_grid(data->map_data->map_grid, y);
				error_message_exit("Malloc failed: pad_map_lines", data, NULL);
			}
			ft_memcpy(new_line, data->map_data->map_grid[y], len);
			while (len < data->map_data->map_w)
				new_line[len++] = ' ';
			new_line[data->map_data->map_w] = '\0';
			free(data->map_data->map_grid[y]);
			data->map_data->map_grid[y] = new_line;
		}
		y++;
	}
}
