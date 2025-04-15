/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colours.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:56:05 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/15 17:33:05 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
		ft_putendl_fd("RGB parsing error", 2);
	free(trimmed_line);
	colour_s.colour = create_rgb(&colour_s);
	//data->map_data->config_count++;
	return (colour_s.colour);
}
