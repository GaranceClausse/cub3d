#include "cub3d.h"

int map3[24][24] = {
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

typedef struct s_floor
{
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	float	posZ;
	float	rowDistance;
	float	floorStepX;
	float	floorStepY;
	float	floorX;
	float	floorY;
	int		cellX;
	int		cellY;
	int		tx;
	int		ty;
	int		floorTexture;
	int		ceilingTexture;
}				t_floor;

typedef struct s_color
{
	int texNum;
	int texX;
	int y;
	int texY;
	double wallX;
	double step;
	double texPos;
}				t_color;


void	init_vrbl_floor(t_data *data, t_floor *floor, int y)
{
		int p;

		p = y -WINDOW_HEIGHT / 2;
		floor->rayDirX0 = data->player.dir_x - data->player.plane_x;
		floor->rayDirY0 = data->player.dir_y - data->player.plane_y;
		floor->rayDirX1 = data->player.dir_x + data->player.plane_x;
		floor->rayDirY1 = data->player.dir_y + data->player.plane_y;

		floor->posZ = 0.5 *WINDOW_HEIGHT;

		floor->rowDistance = floor->posZ / p;

		floor->floorStepX = floor->rowDistance * (floor->rayDirX1 - floor->rayDirX0) / WINDOW_WIDTH;
		floor->floorStepY = floor->rowDistance * (floor->rayDirY1 - floor->rayDirY0) / WINDOW_WIDTH;

		floor->floorX = data->player.pos_x + floor->rowDistance * floor->rayDirX0;
		floor->floorY = data->player.pos_y + floor->rowDistance * floor->rayDirY0;
}

void	calc_vertical_floor(t_data *data, t_floor *floor, int y)
{
	int color;

	for(int x = 0; x < WINDOW_WIDTH; ++x)
	{
		// the cell coord is simply got from the integer parts of floorX and floorY
		floor->cellX = (int)(floor->floorX);
		floor->cellY = (int)(floor->floorY);
		// get the texture coordinate from the fractional part
		floor->tx = (int)(tex_width * (floor->floorX - floor->cellX)) & (tex_width - 1);
		floor->ty = (int)(tex_height * (floor->floorY - floor->cellY)) & (tex_height - 1);
		floor->floorX += floor->floorStepX;
		floor->floorY += floor->floorStepY;
		// choose texture and draw the pixel
		floor->floorTexture = 6;
		floor->ceilingTexture = 6;
		// floor
		color = data->wall.texture[floor->floorTexture][tex_width * floor->ty + floor->tx];
		color = (color >> 1) & 8355711; // make a bit darker
		data->wall.buf[y][x] = color;
		//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
		color = data->wall.texture[floor->ceilingTexture][tex_width * floor->ty + floor->tx];
		color = (color >> 1) & 8355711; // make a bit darker
		data->wall.buf[WINDOW_HEIGHT - y - 1][x] = color;
	}
}

void	calc_floor(t_data *data)
{
	t_floor	floor;

	//FLOOR CASTING
	for(int y = 0; y <WINDOW_HEIGHT; y++)
	{
		init_vrbl_floor(data, &floor, y);
		calc_vertical_floor(data, &floor, y);
	}
}

void	choose_color(t_data *data, int x)
{
	t_color select_clr;
	int		color;

	select_clr.texNum = map3[data->wall.map_x][data->wall.map_y];
	if (data->wall.side == 0)
		select_clr.wallX = data->player.pos_y + data->wall.perp_wall_dist * data->wall.raydir_y;
	else
		select_clr.wallX = data->player.pos_x + data->wall.perp_wall_dist * data->wall.raydir_x;
	select_clr.wallX -= floor(select_clr.wallX);
	select_clr.texX = (int)(select_clr.wallX * (double)tex_width);
	if (data->wall.side == 0 && data->wall.raydir_x > 0)
		select_clr.texX = tex_width - select_clr.texX - 1;
	if (data->wall.side == 1 && data->wall.raydir_y < 0)
		select_clr.texX = tex_width - select_clr.texX - 1;
	select_clr.step = 1.0 * tex_height / data->wall.line_height;
	select_clr.texPos = (data->wall.draw_start - WINDOW_HEIGHT / 2 + data->wall.line_height / 2) * select_clr.step;
	for (int y = data->wall.draw_start; y < data->wall.draw_end; y++)
	{
		select_clr.texY = (int)select_clr.texPos & (tex_height - 1);
		select_clr.texPos += select_clr.step;
		color = data->wall.texture[select_clr.texNum][tex_height * select_clr.texY + select_clr.texX];
		if (data->wall.side == 1)
			color = (color >> 1) & 8355711;
		data->wall.buf[y][x] = color;
	}
}

void	calc(t_data *data)
{
	int	x;
	x = 0;

	calc_floor(data);
	while (x < WINDOW_WIDTH)
	{
		data->wall.camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		data->wall.raydir_x = data->player.dir_x + data->player.plane_x * data->wall.camera_x;
		data->wall.raydir_y = data->player.dir_y + data->player.plane_y * data->wall.camera_x;
		

		data->wall.map_x = (int)data->player.pos_x;
		data->wall.map_y = (int)data->player.pos_y;

		data->wall.delta_dist_x = fabs(1 / data->wall.raydir_x);
		data->wall.delta_dist_y = fabs(1 / data->wall.raydir_y);
		
		data->wall.hit = 0;

		if (data->wall.raydir_x < 0)
		{
			data->wall.step_x = -1;
			data->wall.side_dist_x = (data->player.pos_x - data->wall.map_x) * data->wall.delta_dist_x;
		}
		else
		{
			data->wall.step_x = 1;
			data->wall.side_dist_x = (data->wall.map_x + 1.0 - data->player.pos_x) * data->wall.delta_dist_x;
		}
		if (data->wall.raydir_y < 0)
		{
			data->wall.step_y = -1;
			data->wall.side_dist_y = (data->player.pos_y - data->wall.map_y) * data->wall.delta_dist_y;
		}
		else
		{
			data->wall.step_y = 1;
			data->wall.side_dist_y = (data->wall.map_y + 1.0 - data->player.pos_y) * data->wall.delta_dist_y;
		}

		while (data->wall.hit == 0)
		{
			if (data->wall.side_dist_x < data->wall.side_dist_y)
			{
				data->wall.side_dist_x += data->wall.delta_dist_x;
				data->wall.map_x += data->wall.step_x;
				data->wall.side = 0;
			}
			else
			{
				data->wall.side_dist_y += data->wall.delta_dist_y;
				data->wall.map_y += data->wall.step_y;
				data->wall.side = 1;
			}
			if (map3[data->wall.map_x][data->wall.map_y] > 0) 
				data->wall.hit = 1;
		}
		if (data->wall.side == 0)
			data->wall.perp_wall_dist = (data->wall.map_x - data->player.pos_x + (1 - data->wall.step_x) / 2) / data->wall.raydir_x;
		else
			data->wall.perp_wall_dist = (data->wall.map_y - data->player.pos_y + (1 - data->wall.step_y) / 2) / data->wall.raydir_y;
		
		data->wall.line_height = (int)(WINDOW_HEIGHT / data->wall.perp_wall_dist);
		data->wall.draw_start = -data->wall.line_height / 2 + WINDOW_HEIGHT / 2;
		
		if(data->wall.draw_start < 0)
			data->wall.draw_start = 0;
		
		data->wall.draw_end = data->wall.line_height / 2 + WINDOW_HEIGHT / 2;
		
		if(data->wall.draw_end >= WINDOW_HEIGHT)
			data->wall.draw_end = WINDOW_HEIGHT - 1;
		choose_color(data, x);
		x++;
	}
	draw(data);
}

void	init_texture(t_data*data)
{

	int x = 0;
	int y = 0;

	while (x < tex_width)
	{
		y = 0;
		while (y < tex_height)
		{
			int xorcolor = (x * 256 / tex_width) ^ (y * 256 / tex_height);
			int ycolor = y * 256 / tex_height;
			int xycolor = y * 128 / tex_height + x * 128 / tex_width;
			data->wall.texture[0][tex_width * x + y] = 65536 * 254 * (x != y && x != tex_width - y); //flat red texture with black cross
			data->wall.texture[1][tex_width * x + y] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			data->wall.texture[2][tex_width * x + y] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			data->wall.texture[3][tex_width * x + y] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			data->wall.texture[4][tex_width * x + y] = 256 * xorcolor; //xor green
			data->wall.texture[5][tex_width * x + y] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			data->wall.texture[6][tex_width * x + y] = 65536 * ycolor; //red gradient
			data->wall.texture[7][tex_width * x + y] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		
			++y;
		}
		++x;
	}
}

void	init_color_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	data->wall.buf = (int **)malloc(sizeof(int *) * WINDOW_HEIGHT);
	while (++i < WINDOW_HEIGHT)
		data->wall.buf[i] = (int *)malloc(sizeof(int) * WINDOW_WIDTH);
	i = -1;
	while (++i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			data->wall.buf[i][j++] = 0;
	}
	i = -1;
	while (++i < 8)
	{
		j = 0;
		while (j < tex_width * tex_height)
			data->wall.buf[i][j++] = 0;
	}
}

void	init_vrbl(t_data *data)
{
	data->player.pos_x = 20;
	data->player.pos_y = 11;
	data->player.dir_x = -1;
	data->player.dir_y = 1;
	data->player.plane_x = 0;
	data->player.plane_y = 0.66;
	data->wall.moveSpeed = 1;
	data->wall.rotSpeed = 1;

	init_color_map(data);
	init_texture(data);
}
