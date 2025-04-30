/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:38:47 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/04/25 14:21:32 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/*If any misconfiguration of any kind is encountered in the file, the program
must exit properly and return "Error\n" followed by an explicit error message
of your choice.*/
int	error_message(char *error_message, int code)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error_message, 2);
	return (code);
}

void	error_message_exit(char *error_message, t_data *data)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error_message, 2);
	exit_game(data, EXIT_FAILURE);
}

void	error_message_exit_no_free(char *error_message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error_message, 2);
	exit(EXIT_FAILURE);
}

void	free_map_grid(char **array, int up_to_index)
{
	int	i;

	i = 0;
	while (i < up_to_index)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
