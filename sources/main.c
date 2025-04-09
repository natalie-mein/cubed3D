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
#include "raycasting.h"

int	main(void)
{
	t_data data;

	if (init_data(&data) == 0)
		return (EXIT_FAILURE);
	if (init_game(&data) == 0)
		return (EXIT_FAILURE);
	printf("Before mlx loop\n");
	mlx_loop(data.mlx);
	printf("after mlx_loop\n");
	exit_game(&data);
	return (0);
}

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

