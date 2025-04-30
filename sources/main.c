/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:48:34 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/30 13:49:38 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data	data;

	validate_input(argc, argv[1]);
	init_data(&data);
	parse_file(argv[1], &data); // this function closes the fd // frees data and exits in case of error
	init_textures(&data);
	init_game(&data);
	//mlx_resize_hook(data.mlx, resize_game, &data) <- need to make this
	mlx_loop(data.mlx);
	exit_game(&data, SUCCESS);
	//return (SUCCESS);
} 
