#include "cub3d.h"
# include <math.h>


int map2[24][24] = {
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
							{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
							{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
						};

void	rotate_vector(t_data *data, int angle)
{
	t_player	*player = &data->player;
	int	tmp_x;

	tmp_x = (player->dir_x * cos(angle)) - (player->dir_y * sin(angle));
	player->dir_y = (player->dir_x * sin(angle)) + (player->dir_y * cos(angle));
	player->dir_x = tmp_x;
}



int	handle_input(int key, t_data *data)
{

	if (key == XK_Escape)
	{
		trash(data);
		exit(1);
	}
	if (key == K_W)
	{
		if (!map2[(int)(data->player.pos_x + data->player.dir_x * data->wall.moveSpeed)][(int)(data->player.pos_y)])
			data->player.pos_x += data->player.dir_x * data->wall.moveSpeed;
		if (!map2[(int)(data->player.pos_x)][(int)(data->player.pos_y + data->player.dir_y * data->wall.moveSpeed)])
			data->player.pos_y += data->player.dir_y * data->wall.moveSpeed;
		printf("%d\n", map2[(int)(data->player.pos_x + data->player.dir_x * data->wall.moveSpeed)][(int)(data->player.pos_y)]);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	 }
	if (key == K_S)
	{
		if (!map2[(int)(data->player.pos_x - data->player.dir_x * data->wall.moveSpeed)][(int)(data->player.pos_y)])
			data->player.pos_x -= data->player.dir_x * data->wall.moveSpeed;
		if (!map2[(int)(data->player.pos_x)][(int)(data->player.pos_y - data->player.dir_y * data->wall.moveSpeed)])
			data->player.pos_y -= data->player.dir_y * data->wall.moveSpeed;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	}
	if (key == K_D)
	{
		double oldDirX = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(-data->wall.rotSpeed) - data->player.dir_y * sin(-data->wall.rotSpeed);
		data->player.dir_y = oldDirX * sin(-data->wall.rotSpeed) + data->player.dir_y * cos(-data->wall.rotSpeed);
		double oldPlaneX = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(-data->wall.rotSpeed) - data->player.plane_y * sin(-data->wall.rotSpeed);
		data->player.plane_y = oldPlaneX * sin(-data->wall.rotSpeed) + data->player.plane_y * cos(-data->wall.rotSpeed);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	}
	if (key == K_A)
	{
		double oldDirX = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(data->wall.rotSpeed) - data->player.dir_y * sin(data->wall.rotSpeed);
		data->player.dir_y = oldDirX * sin(data->wall.rotSpeed) + data->player.dir_y * cos(data->wall.rotSpeed);
		double oldPlaneX = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(data->wall.rotSpeed) - data->player.plane_y * sin(data->wall.rotSpeed);
		data->player.plane_y = oldPlaneX * sin(data->wall.rotSpeed) + data->player.plane_y * cos(data->wall.rotSpeed);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	}
	return (0);
}