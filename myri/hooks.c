#include "cub3d.h"

int	handle_keypress(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}

// int	handle_keyrelease(int keysym, void *data)
// {
//     (void)data;
// 	printf("Keyrelease: %d\n", keysym);
// 	return (0);
// }


// int	handle_nothing(void)
// {
// 	return (0);
// }
