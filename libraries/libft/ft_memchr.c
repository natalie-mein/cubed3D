/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:08:01 by nmeintje          #+#    #+#             */
/*   Updated: 2024/04/23 12:26:03 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Works like strchr except it also has  a third parameter 
	that specifies byte size */
void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	con_c;
	size_t			i;

	string = (unsigned char *) str;
	con_c = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (string[i] == con_c)
			return ((void *) &string[i]);
		i++;
	}
	return (NULL);
}
