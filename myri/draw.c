#include "cub3d.h"

void	draw(t_data *data)
{
	for (int y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (int x = 0; x < WINDOW_WIDTH; x++)
		{
			data->img.addr[y * WINDOW_WIDTH + x] = data->wall.buf[y][x];
		}
	}
}

int	main_loop(t_data *data)
{
	calc(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}