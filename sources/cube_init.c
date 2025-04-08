/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:07:50 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/08 13:28:52 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int init_data(t_data *data)
{
    data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (0);
    data->map = malloc(sizeof(t_game));
	if (!data->map)
		return (0);
    data->player->move = malloc(sizeof(t_move));
	if (!data->player->move)
		return (0);
	ft_memset(data->player->move, 0, sizeof(t_move));
    data->image = NULL;

    return (1);
}

int init_game(t_data *data)
{
    data->mlx = mlx_init(WIDTH, HEIGHT, "Test Window", true);
	if (!data->mlx)
		return (0);
    char *map[] = {
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
	data->map->matrix = map;
	draw_map(data, data->map->matrix);
	init_player(data->player, 5, 5, 'N');
	draw_player(data);
	mlx_loop_hook(data->mlx, &render_loop, data);
	mlx_key_hook(data->mlx, &key_hooks, data);
    return (1);
}

