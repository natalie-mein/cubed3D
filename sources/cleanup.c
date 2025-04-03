/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:25:34 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/03 14:42:24 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_game(t_game *game)
{
	int	i;

	if (!game || !game->map)
		return ;
	i = 0;
	while (game->map[i] != NULL)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	free(game);
}