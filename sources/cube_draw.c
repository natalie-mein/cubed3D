
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
	while (map[map_height] != NULL)
		map_height++;
	printf("Map height: %d\n", map_height);
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

//Render function that includes raycasting
void render_game(void *param)
{
	t_data *data = (t_data *)param;

	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
	{
		printf("Failed to create image!\n");
		return;
	}
	//draw_map(data, data->map->matrix);
	move_player(data);
	draw_player(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
}



