/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:52:41 by nmeintje          #+#    #+#             */
/*   Updated: 2025/02/25 15:52:43 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Concatenates 'src' to the end of 'dst' */
void    ft_strcat(char *dst, const char *src)
{
    while (*dst)
        dst++;
    while (*src)
    {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
}
