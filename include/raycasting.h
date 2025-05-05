/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdahlstr <mdahlstr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:16:04 by nmeintje          #+#    #+#             */
/*   Updated: 2025/05/05 15:59:40 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <math.h>
# include <stdbool.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>

# include "cub3D.h"

# define MAP_WIDTH 1000
# define MAP_HEIGHT 600
# define TILE_SIZE 25
# define MOVE_SPEED 0.05
# define PADDING 0.1
# define TEXTURE 640

// structs
typedef struct s_map_data	t_map_data;
typedef struct s_colour		t_colour;
typedef struct s_render		t_render;
typedef struct s_move		t_move;
typedef struct s_player		t_player;
typedef struct s_ray		t_ray;
typedef struct s_text		t_text;
typedef struct s_data		t_data;

void	raycast(t_data *data);
void	draw_player(t_data *data);
void	key_hooks(mlx_key_data_t keydata, void *param);
void	no_key_hook(mlx_key_data_t keydata, t_data *data);
void	move_player(t_data *data);
void	move_forward(t_data *data);
void	move_back(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);
void	render_game(void *param);
void	player_direction(t_data *data);
int		texture_buffer(t_data *data, mlx_texture_t *texture, int direction);
void	calculate_wall_pixels(t_player *player, t_ray *ray);
void	render_wall_pixels(t_data *data, t_ray *ray, int x);
void	render_image(t_data *data);
void	init_textures(t_data *data);
void	init_data(t_data *data);
void	init_game(t_data *data);
void	exit_game(t_data *data, int exit_code);

#endif
