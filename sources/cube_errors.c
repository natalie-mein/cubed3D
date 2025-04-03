/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:56:21 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/02 14:08:45 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    help_msg(void)
{
        ft_putendl_fd("Error\n", 1);
        ft_putendl_fd("Incorrect number of arguments", 1);
        ft_putendl_fd("\tPlease include one map as an argument\n", 1);
        ft_putendl_fd("the map should have the extension .cub", 1);
        ft_putendl_fd("\n", 1);
        ft_putendl_fd("~extra lines~\n", 1);
        ft_putendl_fd("extra lines\n", 1);
        ft_putendl_fd("extra lines\n", 1);
        ft_putendl_fd("extra lines\n", 1);
        ft_putendl_fd("extra lines\n", 1);
        ft_putendl_fd("extra lines", 1);
        exit (1);
}

void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
