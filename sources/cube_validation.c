/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:05:50 by nmeintje          #+#    #+#             */
/*   Updated: 2025/03/06 17:08:51 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed3D.h"

void	ft_file_type(char *input)
{
	if (ft_strrchr(input, '.') == NULL ||
		ft_strncmp(ft_strrchr(input[1], '.'), ".cub", 5) != 0)
		printf("Wrong file type:\nMake sure you use *.cub files.");
	else
		printf("You got the right file type!");
}
