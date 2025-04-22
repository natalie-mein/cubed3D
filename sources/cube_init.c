/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:07:50 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/22 16:15:12 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycasting.h"

// initialise every field in map_data with zeros
void	initialise_map_data(t_data *data)
{
	data->map_data = ft_calloc(1, sizeof(t_map_data));
	if (!data->map_data)
		error_message_exit("Memory allocation failure for map_data struct", data);
	data->map_data->file_len = 0;
	data->map_data->map_grid = NULL;
	data->map_data->no_texture = NULL;
	data->map_data->so_texture = NULL;
	data->map_data->we_texture = NULL;
	data->map_data->ea_texture = NULL;
	data->map_data->floor_colour = -1;
	data->map_data->ceiling_colour = -1;
	data->map_data->config_count = 0;
	data->map_data->map_h = 0;
	data->map_data->map_w = 0;
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit_game(data, EXIT_FAILURE);
	data->player->move = malloc(sizeof(t_move));
	if (!data->player->move)
		exit_game(data, EXIT_FAILURE);
	ft_memset(data->player->move, 0, sizeof(t_move));
	data->image = NULL;
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		exit_game(data, EXIT_FAILURE);
	data->ray->screen_width = WIDTH; // set screen width for raycast
	data->player_dir = '0';
	data->player_y = 0;
	data->player_x = 0;
	initialise_map_data(data);
}

void init_game(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Test Window", true);
	if (!data->mlx)
		error_message_exit("Failed to initialise MLX", data);
	//data->file_data->map = map;
	//draw_map(data, data->map->matrix);
	mlx_loop_hook(data->mlx, &render_game, data);
	//init_player(data->player, 5, 5, 'N'); // this function is temporary until we merge
	player_direction(data);
	//draw_player(data);
	mlx_key_hook(data->mlx, &key_hooks, data);
}
