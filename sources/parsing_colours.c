/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colours.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:56:05 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/16 17:13:09 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// gets numbers from a string, separated by commas
int get_next_number(const char *line, int *index, int colour)
{
	int	start;
	int	num;

	start = *index;
	while (line[*index] == ' ')
		(*index)++;
	start = *index;
	if (line[*index] == '-')
		return (error_message("Invalid colour component: negative number", -1));
	
	if (!ft_isdigit(line[*index]))
		return (error_message("Invalid colour component: missing number", -1));
	while (ft_isdigit(line[*index]))
		(*index)++;
	num = ft_atoi(&line[start]);
	while (line[*index] == ' ')
		(*index)++;
	if (colour != BLUE && line[*index] != ',')
		return (error_message("Invalid colour component: missing comma", -1));
	if (colour == BLUE && line[*index] != '\0' && line[*index] != '\n')
		return (error_message("Invalid colour component: trailing chars", -1));
	if (colour != BLUE && line[*index] == ',')
		(*index)++;
	return (num);
}

// checks for numbers smaller than 0 and larger than 255
// checks if there are other characters after the last number
bool	parse_rgb(char *trimmed_line, t_colour *colour_s)
{
	int	i;

	i = 0;
	colour_s->r = get_next_number(trimmed_line, &i, RED);
	if (colour_s->r == -1)
		return (false);
	colour_s->g = get_next_number(trimmed_line, &i, GREEN);
	if (colour_s->g == -1)
		return (false);
	colour_s->b = get_next_number(trimmed_line, &i, BLUE);
	if (colour_s->b == -1)
		return (false);
	if (colour_s->r < 0 || colour_s->r > 255
		|| colour_s->g < 0 || colour_s->g > 255
		|| colour_s->b < 0 || colour_s->b > 255)
	{
		return (error_message("RGB values must be between 0 and 255", false));
	}
	while (trimmed_line[i] == ' ')
		i++;
	if (trimmed_line[i] != '\0')
		return (false);
	return (true);
}

int	create_rgb(t_colour *colour_s)
{
	return (0xFFFFFF & (colour_s->r << 16 | colour_s->g << 8 | colour_s->b));
}

// get RGB values and converts them to hex colour.
// through bitwise shift operations
int	get_colour(char *line, t_data *data)
{
	char		*trimmed_line;
	t_colour	colour_s;

	ft_bzero(&colour_s, sizeof(t_colour));
	line = line + 1;
	trimmed_line = ft_strtrim(line, " \n");
	if (!parse_rgb(trimmed_line, &colour_s))
	{
		free(trimmed_line);
		free(line);
		exit_game(data, EXIT_FAILURE);
	}
	free(trimmed_line);
	colour_s.colour = create_rgb(&colour_s);
	//data->map_data->config_count++;
	return (colour_s.colour);
}
