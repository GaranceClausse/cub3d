#include "cub3d.h"

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

	for(int x = 0; x < W; ++x)
	{
		// the cell coord is simply got from the integer parts of floorX and floorY
		floor->cellX = (int)(floor->floorX);
		floor->cellY = (int)(floor->floorY);
		// get the texture coordinate from the fractional part
		floor->tx = (int)(tex_w * (floor->floorX - floor->cellX)) & (tex_w - 1);
		floor->ty = (int)(tex_h * (floor->floorY - floor->cellY)) & (tex_h - 1);
		floor->floorX += floor->floorStepX;
		floor->floorY += floor->floorStepY;
		// choose texture and draw the pixel
		floor->floorTexture = 4;
		floor->ceilingTexture = 4;
		// floor
		color = data->wall.texture[floor->floorTexture][tex_w * floor->ty + floor->tx];
		color = (color >> 1) & 8355711; // make a bit darker
		data->wall.buf[y][x] = color;
		//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
		color = data->wall.texture[floor->ceilingTexture][tex_w * floor->ty + floor->tx];
		color = (color >> 1) & 8355711; // make a bit darker
		data->wall.buf[H - y - 1][x] = color;
	}
}

void	calc_floor(t_data *data)
{
	t_floor	floor;

	//FLOOR CASTING
	for(int y = 0; y <H; y++)
	{
		init_vrbl_floor(data, &floor, y);
		calc_vertical_f_c(data, &floor, y);
	}
}
