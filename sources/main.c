/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:48:34 by nmeintje          #+#    #+#             */
/*   Updated: 2025/03/06 17:05:16 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/cubed3D.h"
#include "../include/raycasting.h"

/*int	main(int argc, char **argv)
{
	(void)argv;
	(void)argc;

	t_data	*data = malloc(sizeof(t_data));
	if (!data)
		return (1);

	//if (argc != 2)
	//	help_msg();
	//if (argc == 2)
	//	ft_file_type(argv[1]);
//	mlx_set_setting(MLX_MAXIMIZED, true);

	data->mlx = mlx_init(WIDTH, HEIGHT, "cube3D", false);
	if (!data->mlx)
	{
		printf("mlx_init failed!\n");
		exit(1);
	}

	// Create and display the image.
	data->image = mlx_new_image(data->mlx, 256, 256);
	if (!data->image || (mlx_image_to_window(data->mlx, data->image, 0, 0) < 0))
		ft_error();

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(data->image, 0, 0, 0xFF0000FF);*/
	/*char *map[] = {
        "111111",
        "100001",
        "101101",
        "100001",
        "111111",
        NULL
    }; 

    draw_map(data, map);

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
//	mlx_loop_hook(mlx, ft_hook, mlx);
	printf("Made it to the loop!\n");
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}*/

int	main(void)
{
	t_data *data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (1);

	data->mlx = mlx_init(WIDTH, HEIGHT, "Test Window", false);
	if (!data->mlx)
		return (1);

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

	data->map = malloc(sizeof(t_game));
	if (!data->map)
		return (1);
	data->map->matrix = map;
	data->player->move = malloc(sizeof(t_move));
	if (!data->player->move)
		return (1);
	ft_memset(data->player->move, 0, sizeof(t_move));

	draw_map(data, data->map->matrix);
	init_player(data->player, 5, 5, 'N');
	draw_player(data);
	mlx_loop_hook(data->mlx, &render_loop, data);
	mlx_key_hook(data->mlx, &key_hooks, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	free(data->player);
	free(data);
	return (0);
}

int map[MAP_HEIGHT][MAP_WIDTH] = 
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

/*int	main(void)
{
	t_player player = {
		.pos_x = 12,
		.pos_y = 6,
		.dir_x = -1,
		.dir_y = 0,
		.plane_x = 0,
		.plane_y = 0.66
	};

	t_ray ray = {
		.screen_width = 80.0
	};

	raycast(&player, &ray);
	return (0);
}*/
