/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:07:50 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/16 17:11:29 by mdahlstr         ###   ########.fr       */
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
	data->floor_color = 0xFFFF00FF;
	data->ceiling_color = 0x00FFFFFF;
}

void	init_data(t_data *data)
{
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
	data->render = malloc(sizeof(t_render));
	if (!data->render)
	{
		perror("Failed to allocate render");
		exit(EXIT_FAILURE);
	}
	data->render->pixels = malloc(sizeof(uint32_t *) * HEIGHT);
	if (!data->render->pixels)
		exit_game(data, EXIT_FAILURE);
	int i = 0;
	while (i < HEIGHT)
	{
		data->render->pixels[i] = malloc(sizeof(uint32_t) * WIDTH);
		i++;
	}
	initialise_map_data(data);
}

void init_game(t_data *data)
{
	int	i;

	i = 0;
	data->mlx = mlx_init(WIDTH, HEIGHT, "Test Window", true);
	if (!data->mlx)
		exit_game(data, EXIT_FAILURE);
	/*
	static char *map[] = {
		"111111111111111111111111",
		"100000000000000000000001",
		"101110011001110100010101",
		"100000000000000000000001",
		"100000000000000000000001",
		"100000000000000000000001",
		"111001100111010001100001",
		"100000000000000000000001",
		"100000000000000000000001",
		"100011001100111010001001",
		"100000000000000000000001",
		"111111111111111111111111",
		NULL
	};
	*/
	//data->file_data->map = map;
	mlx_loop_hook(data->mlx, &render_game, data);
	//init_player(data->player, 5, 5, 'N'); // this function is temporary until we merge
	player_direction(data);
	mlx_key_hook(data->mlx, &key_hooks, data);
}
