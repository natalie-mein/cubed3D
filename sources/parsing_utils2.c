/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:06:22 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/05/05 17:31:34 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	has_invalid_dot_position(char *path)
{
	int	len;
	int	i;

	len = ft_strlen(path);
	if (!path || len < 5)
		return (true);
	i = 0;
	while(path[i])
	{
		if (path[i] == '.')
		{
			if (i != 0 && i != len - 4)
				return (true);
		}
		i++;
	}
	return (false);
}