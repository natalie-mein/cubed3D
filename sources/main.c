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

	data->mlx = mlx_init(800, 600, "Test Window", false);
	if (!data->mlx)
		return (1);
	int map_width = 25;
	int map_height = 0;
	while (map[map_height])
		map_height++;
		
	data->image = mlx_new_image(data->mlx, map_width * 32, map_height * 32);

	//data->image = mlx_new_image(data->mlx, 100, 100);
	if (!data->image)
		return (1);

	//for (int y = 0; y < 100; y++)
	//	for (int x = 0; x < 100; x++)
	//		mlx_put_pixel(img, x, y, 0xFF0000FF); // red block
	/*char *map[] = {
		"1111111",
		"1000001",
		"1000001",
		"1111111",
		NULL
	};*/

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
			
	for (int y = 0; map[y]; y++)
	{
		for (int x = 0; map[y][x]; x++)
		{
			uint32_t color = (map[y][x] == '1') ? 0xFFFFFFFF : 0x222222FF;
			for (int dy = 0; dy < 32; dy++)
				for (int dx = 0; dx < 32; dx++)
					mlx_put_pixel(data->image, x * 32 + dx, y * 32 + dy, color);
		}
	};

	//draw_map(data, map);

	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
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
