/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:45:55 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/15 18:45:17 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/raycasting.h"
//#include "../include/parsing.h"
#include "cub3D.h"
//free2darray 

void	free_if_allocated(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	free_map_data(t_map_data *map_data)
{
	int	i;

	if (!map_data)
		return ;
	free_if_allocated(map_data->no_texture);
	free_if_allocated(map_data->so_texture);
	free_if_allocated(map_data->we_texture);
	free_if_allocated(map_data->ea_texture);
	i = 0;
	if (map_data->map_grid)
	{
		while (map_data->map_grid[i] != NULL)
		{
			free(map_data->map_grid[i]);
			i++;
		}
		free(map_data->map_grid);
	}
	free(map_data);
}

// free2darray

void	free_data(t_data *data)
{
	int i;

	i = 0;
	if (data->map_data)
		free_map_data(data->map_data); ///////////////////// ATTENTION
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
	free_data(data);
	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	//free(data); // Why is this causing an Invalid Free error in Valgrind?
	exit(exit_code);
}



