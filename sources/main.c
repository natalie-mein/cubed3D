/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:48:34 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/29 16:39:00 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data		data;
	char		*filename;

	(void)argc; // this should be 2
	//validate_input(argc, argv[1]); // no memory freeing necessary on error.
	filename = argv[1];
	init_data(&data);
	parse_file(filename, &data); // this function closes the fd // frees data and exits in case of error
	init_textures(&data);
	init_game(&data);
	//mlx_resize_hook(data.mlx, resize_game, &data) <- need to make this
	mlx_loop(data.mlx);
	exit_game(&data, SUCCESS);
	//return (SUCCESS);
	//
}
