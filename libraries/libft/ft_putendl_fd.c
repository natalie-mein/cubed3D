/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:10:30 by nmeintje          #+#    #+#             */
/*   Updated: 2024/04/29 14:39:25 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Writes string 's' to file descriptor 'fd', followed by a new line */
void	ft_putendl_fd(char *s, int fd)
{
	int	n;

	n = '\n';
	if (s)
	{
		write(fd, s, ft_strlen(s));
		write(fd, &n, 1);
	}
}
