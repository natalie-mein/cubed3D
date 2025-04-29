/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:58:46 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/17 10:58:48 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

/*
Returns the RGBA color calue of the pixels at row i, column j
*/
uint32_t    pixel_color(int i, int j, mlx_texture_t *texture)
{
    int index;

    index = (i * texture->width + j) * 4;
    return (*(uint32_t *)(texture->pixels + index));
}

/*
Copies all the pixel colors from the loaded texture into the pixel buffer 
*/
int texture_buffer(t_data *data, mlx_texture_t *texture, int direction)
{
    uint32_t    *pixels;
    uint32_t    i;
    uint32_t    j;

    i = 0;
    pixels = ft_calloc((texture->height * texture->width), sizeof(uint32_t));
    if (!pixels)
        return (ERROR);
    while (i < texture->height)
    {
        j = 0;
        while (j < texture->width)
        {
            pixels[i * texture->width + j] = pixel_color(i, j, texture);
            j++;
        }
        i++;
    }
    data->render->text_buf[direction] = pixels;
    return (SUCCESS);
}

