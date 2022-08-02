#include "../include/cub.h"

void	rotate_vector(t_data *data, int angle)
{
	t_player	*player = &data->player;
	int	tmp_x;

	tmp_x = (player->dir_x * cos(angle)) - (player->dir_y * sin(angle));
	player->dir_y = (player->dir_x * sin(angle)) + (player->dir_y * cos(angle));
	player->dir_x = tmp_x;
}


void	move_key(t_data *data)
{
	if (data->key_forward == 1)
	{
		if (data->tab_map[(int)(data->player.pos_y + data->player.dir_y * data->wall.moveSpeed)][(int)(data->player.pos_x)] == '0')
			data->player.pos_y += data->player.dir_y * data->wall.moveSpeed;
		if (data->tab_map[(int)(data->player.pos_y)][(int)(data->player.pos_x + data->player.dir_x * data->wall.moveSpeed)] == '0')
			data->player.pos_x += data->player.dir_x * data->wall.moveSpeed;
	}
	if (data->key_back == 1)
	{
		if (data->tab_map[(int)(data->player.pos_y - data->player.dir_y * data->wall.moveSpeed)][(int)(data->player.pos_x)] == '0')
			data->player.pos_y -= data->player.dir_y * data->wall.moveSpeed;
		if (data->tab_map[(int)(data->player.pos_y)][(int)(data->player.pos_x - data->player.dir_x * data->wall.moveSpeed)] == '0')
			data->player.pos_x -= data->player.dir_x * data->wall.moveSpeed;
	}
	if (data->key_left == 1)
	{
		if (data->tab_map[(int)(data->player.pos_y + data->player.dir_x * data->wall.moveSpeed)][(int)(data->player.pos_x)] == '0')
			data->player.pos_y += data->player.dir_x * data->wall.moveSpeed;
		if (data->tab_map[(int)(data->player.pos_y)][(int)(data->player.pos_x - data->player.dir_y * data->wall.moveSpeed)] == '0')
			data->player.pos_x -= data->player.dir_y * data->wall.moveSpeed;
	}
	if (data->key_right == 1)
	{
		if (data->tab_map[(int)(data->player.pos_y - data->player.dir_x * data->wall.moveSpeed)][(int)(data->player.pos_x)] == '0')
			data->player.pos_y -= data->player.dir_x * data->wall.moveSpeed;
		if (data->tab_map[(int)(data->player.pos_y)][(int)(data->player.pos_x + data->player.dir_y * data->wall.moveSpeed)] == '0')
			data->player.pos_x += data->player.dir_y * data->wall.moveSpeed;
	}
}

void	rotate_key(t_data *data)
{
	double oldDirX;
	double oldPlaneX;
	int		opt = 1;

	if (data->key_r_left == 1 || data->key_r_right == 1)
	{
		if (data->key_r_left == 1)
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
}
