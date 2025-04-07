
#include "../include/raycasting.h"

void draw_tile(t_data *data, int x, int y, uint32_t color)
{
	int i;
	int j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_put_pixel(data->image, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void draw_map(t_data *data, char **map)
{
	int map_height;
	int map_width; // Assuming all rows same length
	int y;
	int x;
	char    tile;
	uint32_t color;

	map_height = 0;
	x = 0;
	y = 0;
	map_width = ft_strlen(map[0]);
	while (map[map_height])
		map_height++;
	data->image = mlx_new_image(data->mlx, map_width * TILE_SIZE, map_height * TILE_SIZE);
	if (!data->image)
		return;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			tile = map[y][x];
			if (tile == '1')
				color = 0xFFFFFFFF; // white wall
			else if (tile == '0')
				color = 0x222222FF; // dark floor
			else
				color = 0xFF0000FF; // red for unknown
			draw_tile(data, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}



