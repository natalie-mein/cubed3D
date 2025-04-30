/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_dbl_ptr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:42:20 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/25 11:42:22 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*frees an array of chars*/
void	ft_free_dbl_ptr (char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}
