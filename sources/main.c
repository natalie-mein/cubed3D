/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:48:34 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/22 17:38:21 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// exit() is allowed in the project
// so the program might stop at void functions
/*
int	main(int argc, char **argv)
{
	t_file_data	*file_data;
	t_data		data;
	char		*file_name;

	(void)argc;
	file_data = NULL;
	file_name = argv[1];
	//validate_input(argc, argv[1]); // no memory freeing necessary on error.
	parse_file(file_name, file_data);
	//	mlx_set_setting(MLX_MAXIMIZED, true);
	
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "~ CUB3D ~", true);
	if (!mlx)
		ft_error();

	// Create and display the image.
	//mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	//if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	//	ft_error();

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	//	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_file_data(file_data); // free the file_data struct.
	return (SUCCESS);
}
*/

// Natalie Main

int	main(int argc, char **argv)
{
	t_data		data;
	char		*filename;

	(void)argc; // this should be 2
	//validate_input(argc, argv[1]); // no memory freeing necessary on error.
	filename = argv[1];
	init_data(&data);
	parse_file(filename, &data);
	init_game(&data);
	//printf("Before mlx loop\n");
	mlx_loop(data.mlx);
	//printf("after mlx_loop\n");
	//exit_game(&data, SUCCESS);
	free_data(&data);
	return (SUCCESS);
} 
