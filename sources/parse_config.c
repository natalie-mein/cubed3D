/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:13:42 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/05/06 12:19:49 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parse_config(t_data *data)
{
	if (!data->map_data->no_texture || !data->map_data->so_texture
		|| !data->map_data->we_texture || !data->map_data->ea_texture
		|| data->map_data->floor_colour == 1
		|| data->map_data->ceiling_colour == 1
		|| data->map_data->config_count < 6)
		error_message_exit("Missing configuration elements", data);
	else if (data->map_data->config_count > 6
		|| data->map_data->floor_colour == 2
		|| data->map_data->ceiling_colour == 2)
		error_message_exit("Duplicated configuration element(s)", data);
}
