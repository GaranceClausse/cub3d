#include "../include/cub.h"

int	handle_keypress(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}


int	handle_input(int key, t_data *data)
{

	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (key == K_A || key == K_D || key == K_S ||  key == K_W)
	{
		move_key(key, data);
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
	}
	if (key == XK_Right || key == XK_Left)
	{
		rotate_key(key, data);
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
	}
	return (0);
}