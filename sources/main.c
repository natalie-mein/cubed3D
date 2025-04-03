/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:48:34 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/03 10:23:43 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// exit() is allowed in the project
// so the program might stop at void functions
int	main(int argc, char **argv)
{
	t_game	*game;

	game = NULL;
	validate_input(argc, argv[1]); // no memory freeing necessary on error.
	parse_map(argv[1], game);
//	mlx_set_setting(MLX_MAXIMIZED, true);
	
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();

	/* Do stuff */

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	//	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (SUCCESS);
}
