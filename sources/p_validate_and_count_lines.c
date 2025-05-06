/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_validate_and_count_lines.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:59:17 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/05/06 12:19:40 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// Skips spaces and checks the first character of every line
// Accepted chars: N S E W F C 1, all types of spaces, newline
// and null terminator.
// Returns TRUE if a character is NOT on the list above
// Returns FALSE if the character is as expected
static bool	wrong_char_in_line(char *line)
{
	int		i;
	char	c;

	i = skip_whitespace(line);
	c = line[i];
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != 'F' && c != 'C'
		&& c != '1' && !ft_iswhitespace(c) && c != '\n' && c != '\0')
		return (true);
	return (false);
}

static void	validate_line(char *line, int fd, t_data *data)
{
	if (wrong_char_in_line(line))
	{
		if (line)
			free(line);
		line = NULL;
		close(fd);
		error_message_exit("Wrong character found in file.", data);
	}
	if (is_map_line(line))
		data->map_data->map_h++;
	free(line);
}

/* Checks the entire file for lines starting with strange characters */
/* Counts file lines and map lines (map_h) */
void	validate_and_count_lines(char *filename, t_data *data)
{
	int		i;
	char	*line;
	int		fd;

	fd = get_fd(filename, data);
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		if (i >= MAX_LINES - 1)
		{
			if (line)
				free(line);
			line = NULL;
			close(fd);
			error_message_exit("File has too many lines", data);
		}
		validate_line(line, fd, data);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	if (data->map_data->map_h < 3)
		error_message_exit("Map empty or too small.", data);
	data->map_data->file_len = i;
}
