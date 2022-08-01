#include "../include/cub.h"

/*
int		ft_key_press(int keycode, t_recup *recup)
{
	if (keycode == FORWARD_W_Z)
		recup->data.forward = 1;
	else if (keycode == BACK_S_S)
		recup->data.back = 1;
	else if (keycode == LEFT_A_Q)
		recup->data.left = 1;
	else if (keycode == RIGHT_D_D)
		recup->data.right = 1;
	else if (keycode == ROTATE_LEFT)
		recup->data.rotate_left = 1;
	else if (keycode == ROTATE_RIGHT)
		recup->data.rotate_right = 1;
	else if (keycode == 65307)
		ft_error(recup, "Non jrigole\n");
	return (1);
}

int		ft_key_release(int keycode, t_recup *recup)
{
	if (keycode == FORWARD_W_Z)
		recup->data.forward = 0;
	else if (keycode == BACK_S_S)
		recup->data.back = 0;
	else if (keycode == LEFT_A_Q)
		recup->data.left = 0;
	else if (keycode == RIGHT_D_D)
		recup->data.right = 0;
	else if (keycode == ROTATE_LEFT)
		recup->data.rotate_left = 0;
	else if (keycode == ROTATE_RIGHT)
		recup->data.rotate_right = 0;
	return (1);
}
*/
int	handle_keypress(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}

int	handle_release(int key, t_data *data)
{
	if (key == K_A)
		data->key_left = 0;
	else if (key == K_D)
		data->key_right = 0;
	else if (key == K_S)
		data->key_back = 0;
	else if (key == K_W)
		data->key_forward = 0;
	else if (key == XK_Right)
		data->key_r_right = 0;
	else if (key == XK_Left)
		data->key_r_left = 0;
	return (0);
}

int	handle_input(int key, t_data *data)
{

	if (key == K_A)
		data->key_left = 1;
	else if (key == K_D)
		data->key_right = 1;
	else if (key == K_S)
		data->key_back = 1;
	else if (key == K_W)
		data->key_forward = 1;
	else if (key == XK_Right)
		data->key_r_right = 1;
	else if (key == XK_Left)
		data->key_r_left = 1;
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}
