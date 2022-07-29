#include "../include/cub.h"
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


void	move_key(int key, t_data *data)
{
	if (key == K_W)
	{
		if (!map2[(int)(data->player.pos_x + data->player.dir_x * data->wall.moveSpeed)][(int)(data->player.pos_y)])
			data->player.pos_x += data->player.dir_x * data->wall.moveSpeed;
		if (!map2[(int)(data->player.pos_x)][(int)(data->player.pos_y + data->player.dir_y * data->wall.moveSpeed)])
			data->player.pos_y += data->player.dir_y * data->wall.moveSpeed;
	}
	if (key == K_S)
	{
		if (!map2[(int)(data->player.pos_x - data->player.dir_x * data->wall.moveSpeed)][(int)(data->player.pos_y)])
			data->player.pos_x -= data->player.dir_x * data->wall.moveSpeed;
		if (!map2[(int)(data->player.pos_x)][(int)(data->player.pos_y - data->player.dir_y * data->wall.moveSpeed)])
			data->player.pos_y -= data->player.dir_y * data->wall.moveSpeed;
	}
	if (key == K_D)
	{
		if (!map2[(int)(data->player.pos_x + data->player.dir_y * data->wall.moveSpeed)][(int)(data->player.pos_y)])
			data->player.pos_x += data->player.dir_y * data->wall.moveSpeed;
		if (!map2[(int)(data->player.pos_x)][(int)(data->player.pos_y - data->player.dir_x * data->wall.moveSpeed)])
			data->player.pos_y -= data->player.dir_x * data->wall.moveSpeed;
	}
	if (key == K_A)
	{
		if (!map2[(int)(data->player.pos_x - data->player.dir_y * data->wall.moveSpeed)][(int)(data->player.pos_y)])
			data->player.pos_x -= data->player.dir_y * data->wall.moveSpeed;
		if (!map2[(int)(data->player.pos_x)][(int)(data->player.pos_y + data->player.dir_x * data->wall.moveSpeed)])
			data->player.pos_y += data->player.dir_x * data->wall.moveSpeed;
	}
}

void	rotate_key(int key, t_data *data)
{
	double oldDirX;
	double oldPlaneX;
	int		opt = 1;

	if (key == XK_Left)
		opt = -1;
	oldDirX = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-data->wall.rotSpeed * opt)
						- data->player.dir_y * sin(-data->wall.rotSpeed * opt);
	data->player.dir_y = oldDirX * sin(-data->wall.rotSpeed * opt)
					+ data->player.dir_y * cos(-data->wall.rotSpeed * opt);
	oldPlaneX = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-data->wall.rotSpeed * opt)
						- data->player.plane_y * sin(-data->wall.rotSpeed * opt);
	data->player.plane_y = oldPlaneX * sin(-data->wall.rotSpeed * opt)
						+ data->player.plane_y * cos(-data->wall.rotSpeed * opt);
}
