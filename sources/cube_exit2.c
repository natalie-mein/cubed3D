/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_exit2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:55:50 by mdahlstr          #+#    #+#             */
/*   Updated: 2025/05/06 14:52:41 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_text_buf(uint32_t *text_buf[4])
{
	int	i;

	if (!text_buf)
		return ;
	i = 0;
	while (i < 4)
	{
		if (text_buf[i])
			free(text_buf[i]);
		i++;
	}
}

void	free_pixels_array(uint32_t **pixels, int height)
{
	int	i;

	if (!pixels)
		return ;
	i = 0;
	while (i < height)
	{
		if (pixels[i])
			free(pixels[i]);
		i++;
	}
	free(pixels);
}

void	free_render(t_render *render)
{
	free_text_buf(render->text_buf);
	free_pixels_array(render->pixels, HEIGHT);
	free(render);
}

void	free_texture(t_data *data)
{
	if (data->text->north)
		mlx_delete_texture(data->text->north);
	if (data->text->south)
		mlx_delete_texture(data->text->south);
	if (data->text->east)
		mlx_delete_texture(data->text->east);
	if (data->text->west)
		mlx_delete_texture(data->text->west);
	if (data->text)
		free(data->text);
}
