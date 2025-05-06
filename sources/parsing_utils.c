/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:24 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/05/06 16:24:05 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Checks for dot in the wrong position.
// Compares extension to expected 4 characters.
bool	is_right_extension(char *filename, size_t len, char *ext)
{
	if (has_invalid_dot_position(filename))
		return (false);
	if (filename[len - 4] != ext[0] || filename[len - 3] != ext[1]
		|| filename[len - 2] != ext[2] || filename[len - 1] != ext[3])
		return (false);
	return (true);
}

// Returns true for all lines starting and ending with '1'
bool	is_map_line(const char *line)
{
	int	start;
	int	end;

	start = 0;
	if (!line)
		return (false);
	while (line[start] && ft_iswhitespace(line[start]))
		start++;
	if (line[start] != '1')
		return (false);
	end = ft_strlen(line) - 1;
	while (end > start && ft_iswhitespace(line[end]))
		end--;
	if (line[end] != '1')
		return (false);
	return (true);
}

void	free_map_grid(char **array, int up_to_index)
{
	int	i;

	i = 0;
	while (i < up_to_index)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	skip_whitespace(char *line)
{
	int	x;

	x = 0;
	while (ft_iswhitespace(line[x]))
		x++;
	return (x);
}

int	get_fd(char *filename, t_data *data)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_message_exit("Failed to open file", data, NULL);
	return (fd);
}
