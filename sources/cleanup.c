/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:25:34 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/10 13:28:26 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_file_data(t_file_data *file_data)
{
	int	i;

	if (!file_data || !file_data->file)
		return ;
	i = 0;
	while (file_data->file[i] != NULL)
	{
		free(file_data->file[i]);
		i++;
	}
	free(file_data->file);
	free(file_data->north_texture);
	free(file_data->south_texture);
	free(file_data->west_texture);
	free(file_data->east_texture);
	free(file_data);
}