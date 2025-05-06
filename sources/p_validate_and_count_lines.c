/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_validate_and_count_lines.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:59:17 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/05/06 20:02:08 by mdahlstr         ###   ########.fr       */
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

static bool	is_line_empty_or_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (!ft_iswhitespace(line[i]) && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

// also change validate_line to bool + errmsg
static bool	validate_line(char *line, t_data *data)
{
	if (wrong_char_in_line(line))
		return (false);
	if (is_map_line(line))
		data->map_data->map_h++;
	return (true);
}

// change signature to return success/failure + error message
static char	*process_map_line(t_data *data, char *line, bool *map_started,
	bool *map_ended)
{
	if (++data->map_data->file_len >= MAX_LINES)
		return ("File has too many lines");
	if (is_map_line(line))
	{
		if (*map_ended)
			return ("Extraneous content after map.");
		*map_started = true;
		data->map_data->map_h++;
	}
	else if (*map_started && !is_line_empty_or_whitespace(line))
	{
		*map_ended = true;
		return ("Extraneous content after map.");
	}
	else if (!*map_started && !validate_line(line, data))
		return ("Wrong character found in map file.");
	return (NULL);
}

void	validate_and_count_lines(char *filename, t_data *data)
{
	int		fd;
	char	*line;
	char	*errmsg;
	bool	map_started;
	bool	map_ended;

	fd = get_fd(filename, data);
	map_started = false;
	map_ended = false;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		errmsg = process_map_line(data, line, &map_started, &map_ended);
		free(line);
		if (errmsg)
		{
			close(fd);
			error_message_exit(errmsg, data, NULL);
		}
	}
	close(fd);
	if (data->map_data->map_h < 3)
		error_message_exit("Map empty or too small.", data, NULL);
}
