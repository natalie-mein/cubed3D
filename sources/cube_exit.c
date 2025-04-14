/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:45:55 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/14 16:29:50 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/raycasting.h"
//#include "../include/parsing.h"
#include "cub3D.h"
//free2darray 

void	free_map_data(t_map_data *map_data)
{
	int	i;

	if (!map_data)
		return ;
	i = 0;
	while (map_data->map_grid[i] != NULL)
	{
		free(map_data->map_grid[i]);
		i++;
	}
	free(map_data->map_grid);
	// Should these all be checked as well?
	free(map_data->no_texture);
	free(map_data->so_texture);
	free(map_data->we_texture);
	free(map_data->ea_texture);
	free(map_data);
}

// free2darray

void    free_data(t_data *data)
{
	int i;

	i = 0;
	if (data->map_data)
		free_map_data(data->map_data); ///////////////////// ATTENTION
	if (data->player)
		free(data->player);
	//if (data->map_data)
	//	free(data->map_data);
	if (data->ray)
		free(data->ray);
   // if (data)
	//	free(data);
}

// exits with exit_code or simply returns in case of success
void    exit_game(t_data *data, int exit_code)
{
	free_data(data);
	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	exit(exit_code);
}



