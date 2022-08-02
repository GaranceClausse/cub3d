#include "../include/cub.h"

void	init_vrbl_floor(t_data *data, t_floor *floor, int y)
{
		int p;

		p = y -H / 2;
		floor->rayDirX0 = data->player.dir_x - data->player.plane_x;
		floor->rayDirY0 = data->player.dir_y - data->player.plane_y;
		floor->rayDirX1 = data->player.dir_x + data->player.plane_x;
		floor->rayDirY1 = data->player.dir_y + data->player.plane_y;

		floor->posZ = 0.5 *H;

		floor->rowDistance = floor->posZ / p;

		floor->floorStepX = floor->rowDistance * (floor->rayDirX1 - floor->rayDirX0) / W;
		floor->floorStepY = floor->rowDistance * (floor->rayDirY1 - floor->rayDirY0) / W;

		floor->floorX = data->player.pos_x + floor->rowDistance * floor->rayDirX0;
		floor->floorY = data->player.pos_y + floor->rowDistance * floor->rayDirY0;
}

void	calc_vertical_f_c(t_data *data, t_floor *floor, int y)
{
	int color;
	int	i;
	i = 0;
	while (i < W)
	{
		floor->cellX = (int)(floor->floorX);
		floor->cellY = (int)(floor->floorY);
		floor->tx = (int)(tex_w * (floor->floorX - floor->cellX)) & (tex_w - 1);
		floor->ty = (int)(tex_h * (floor->floorY - floor->cellY)) & (tex_h - 1);
		floor->floorX += floor->floorStepX;
		floor->floorY += floor->floorStepY;
		floor->floorTexture = 1;
		floor->ceilingTexture = 2;
		color = data->wall.texture[floor->floorTexture][tex_w * floor->ty + floor->tx];
		color = (color >> 1) & 8355711;
		data->buf[y][i] = color;
		color = data->wall.texture[floor->ceilingTexture][tex_w * floor->ty + floor->tx];
		color = (color >> 1) & 8355711;
		data->buf[H - y - 1][i] = color;
		++i;
	}
}

void	calc_floor(t_data *data)
{
	t_floor	floor;

	int	i;
	i = 0;
	while (i <H)
	{
		init_vrbl_floor(data, &floor, i);
		calc_vertical_f_c(data, &floor, i);
		++i;
	}
}
