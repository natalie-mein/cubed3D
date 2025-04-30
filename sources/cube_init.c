/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:07:50 by nmeintje          #+#    #+#             */
/*   Updated: 2025/04/30 17:35:56 by mdahlstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycasting.h"

// initialise every field in map_data with zeros
void	initialise_map_data(t_data *data)
{
	data->map_data = ft_calloc(1, sizeof(t_map_data));
	if (!data->map_data)
		error_message_exit("Memory allocation failure for map_data struct", data);
	data->map_data->file_len = 0;
	data->map_data->map_grid = NULL;
	data->map_data->no_texture = NULL;
	data->map_data->so_texture = NULL;
	data->map_data->we_texture = NULL;
	data->map_data->ea_texture = NULL;
	data->map_data->floor_colour = 1;
	data->map_data->ceiling_colour = 1;
	data->map_data->floor_set = 0;
	data->map_data->ceiling_set = 0;
	data->map_data->config_count = 0;
	data->map_data->map_h = 0;
	data->map_data->map_w = 0;
}

void	init_render(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->render = ft_calloc(1, sizeof(t_render));
	if (!data->render)
	{
		perror("Failed to allocate render");
		exit(EXIT_FAILURE);
	}
	data->render->pixels = ft_calloc(HEIGHT, sizeof(uint32_t *));
	if (!data->render->pixels)
		exit_game(data, EXIT_FAILURE);
	while (i < HEIGHT)
	{
		data->render->pixels[i] = ft_calloc(WIDTH, sizeof(uint32_t));
		if (!data->render->pixels[i])
			error_message_exit("Memory allocation failure for pixels", data);
		i++;
	}
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx = NULL;
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		exit_game(data, EXIT_FAILURE);
	data->player->move = malloc(sizeof(t_move));
	if (!data->player->move)
		exit_game(data, EXIT_FAILURE);
	ft_memset(data->player->move, 0, sizeof(t_move));
	data->image = NULL;
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		exit_game(data, EXIT_FAILURE);
	data->ray->screen_width = WIDTH; // set screen width for raycast
	data->player_dir = '0';
	data->player_y = 0;
	data->player_x = 0;
	data->text = malloc(sizeof(t_text));
	if (!data->text)
		exit_game(data, EXIT_FAILURE);
	init_render(data);
	initialise_map_data(data);
}

void	init_textures(t_data *data)
{
	data->text->north = mlx_load_png(data->map_data->no_texture);
	data->text->south = mlx_load_png(data->map_data->so_texture);
	data->text->east = mlx_load_png(data->map_data->ea_texture);
	data->text->west = mlx_load_png(data->map_data->we_texture);
	if (!data->text->north || !data->text->south || !data->text->east
		|| !data->text->west)
		error_message_exit("Memory allocation failure for textures", data);
	if (texture_buffer(data, data->text->north, 0) == 1)
		exit_game(data, EXIT_FAILURE);
	if (texture_buffer(data, data->text->south, 1) == 1)
		exit_game(data, EXIT_FAILURE);
	if (texture_buffer(data, data->text->east, 2) == 1)
		exit_game(data, EXIT_FAILURE);
	if (texture_buffer(data, data->text->west, 3) == 1)
		exit_game(data, EXIT_FAILURE);
}


void init_game(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!data->mlx)
		exit_game(data, EXIT_FAILURE);
	//draw_map(data, data->map->matrix);
	//mlx_loop_hook(data->mlx, &render_game, data);
	player_direction(data);
	mlx_key_hook(data->mlx, &key_hooks, data);
	mlx_loop_hook(data->mlx, &render_game, data);
}
