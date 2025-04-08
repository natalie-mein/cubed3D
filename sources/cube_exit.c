/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:45:55 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/08 13:45:57 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycasting.h"

void    free_data(t_data *data)
{
    int i;

    i = 0;
    if (data->player)
        free(data->player);
    if (data->map)
        free(data->map);
    if (data->ray)
        free(data->ray);
    while (i < 0)
    {
        if (data->textures[i])
            free(data->textures[i]);
        i++;
    }
    
    if (data)
    	free(data);
}

void    exit_game(t_data *data)
{
    free_data(data);
    if (data->mlx)
    {
        mlx_close_window(data->mlx);
        mlx_terminate(data->mlx);
    }
}



