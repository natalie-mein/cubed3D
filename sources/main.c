/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:48:34 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/03 14:14:08 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../include/cub3D.h"
#include "raycasting.h"

int	main(void)
{
	t_data data;

	if (init_data(&data) == 0)
		return (EXIT_FAILURE);
	if (init_game(&data) == 0)
		return (EXIT_FAILURE);
	//printf("Before mlx loop\n");
	mlx_loop(data.mlx);
	//printf("after mlx_loop\n");
	exit_game(&data);
	return (0);
}

/*// exit() is allowed in the project
// so the program might stop at void functions
int	main(int argc, char **argv)
{
	(void)argv;

	if (argc != 2)
		help_msg();
	if (argc == 2)
		ft_file_type(argv[1]);
//	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();

	/* Do stuff */

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
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
