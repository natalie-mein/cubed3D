/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:45:55 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/22 16:20:00 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/raycasting.h"
//#include "../include/parsing.h"
#include "cub3D.h"

void	free_2d_array(char **array, int height)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < height)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_if_allocated(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	free_map_data(t_map_data *map_data, int height)
{
	if (!map_data)
		return ;
	free_if_allocated(map_data->no_texture);
	free_if_allocated(map_data->so_texture);
	free_if_allocated(map_data->we_texture);
	free_if_allocated(map_data->ea_texture);
	if (map_data->map_grid)
		free_2d_array(map_data->map_grid, height);
	free(map_data);
}

// free2darray

void	free_data(t_data *data)
{
	int i;

	i = 0;
	if (data->map_data)
		free_map_data(data->map_data, data->map_data->map_h);
	if (data->player->move)
		free(data->player->move);
	if (data->player)
		free(data->player);
	if (data->ray)
		free(data->ray);
	// if (data)
	//	free(data);
}

void	exit_game(t_data *data, int exit_code)
{	
	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	if (data)
		free_data(data);
	//free(data); // Why is this causing an Invalid Free error in Valgrind?
	exit(exit_code);
}



