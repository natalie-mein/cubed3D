/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:53:43 by nmeintje          #+#    #+#             */
/*   Updated: 2024/04/30 14:38:22 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Makes a copy of src, after allocating sufficient memory for it. */
char	*ft_strdup(char *src)
{
	int		i;
	char	*dup;

	i = ft_strlen(src) + 1;
	dup = (char *)malloc(i * sizeof (char));
	if (dup == NULL)
		return (NULL);
	return (ft_strcpy(dup, src));
}
