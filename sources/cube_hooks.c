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

#include "cub3D.h"

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
