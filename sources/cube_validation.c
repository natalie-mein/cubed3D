/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:05:50 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/02 11:54:05 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed3D.h"

// parsing map file
void	ft_file_type(char *input)
{
	if (ft_strrchr(input, '.') == NULL ||
		ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 5) != 0)
		printf("Wrong file type:\nMake sure you use *.cub files.");
	else
		printf("You got the right file type!");
}
