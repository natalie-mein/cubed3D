/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:51:23 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/02 14:08:48 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void ft_hook(void* param)
{
	//const mlx_t* mlx = param;
	(void)param;

	int width;
	int height;

	width = 1024;
	height = 512;

	printf("WIDTH: %d | HEIGHT: %d\n", width, height);
}

void	no_key_hook(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.action == MLX_RELEASE)
	{
		data->player->move->left = false;
		data->player->move->right = false;
		data->player->move->back = false;
		data->player->move->forward = false;
		data->player->move->rotate_l = false;
		data->player->move->rotate_r = false;
	}
}

void	key_hooks(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_A)
			data->player->move->left = true;
		else if (keydata.key == MLX_KEY_D)
			data->player->move->right = true;
		else if (keydata.key == MLX_KEY_S)
			data->player->move->back = true;
		else if (keydata.key == MLX_KEY_W)
			data->player->move->forward = true;
		else if (keydata.key == MLX_KEY_LEFT)
			data->player->move->rotate_l = true;
		else if (keydata.key == MLX_KEY_RIGHT)
			data->player->move->rotate_r = true;
		//else if (keydata.key == MLX_KEY_UP)
		// maybe color change floor and ceiling?
		//else if (keydata.key == MLX_KEY_DOWN)
		//do some other thing
	}
	no_key_hook(keydata, data);
}

void move_player(t_data *data)
{
	if (data->player->move->left)
		move_left(data);
	else if (data->player->move->right)
		move_right(data);
	else if (data->player->move->back)
		move_back(data);
	else if (data->player->move->forward)
		move_forward(data);
	else if (data->player->move->rotate_l)
		rotate_left(data);
	else if (data->player->move->rotate_r)
		rotate_right(data);
}
