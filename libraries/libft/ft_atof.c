/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:45:26 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/25 13:34:54 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ascii to float conversion */
double	ft_atof(char *str)
{
	double	result;
	int		sign;
	int		decimals;

	result = 0.0;
	sign = 1;
	decimals = 1;
	if (str == NULL)
		return (0.0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str++ - '0');
		decimals *= 10;
	}
	return ((result / decimals) * sign);
}
