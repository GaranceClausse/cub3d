#include "cub3d.h"

int map[24][24] = {
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

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
		{
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		}
		i -= 8;
	}
}

void	verLine(t_data *info, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		img_pix_put(&info->img, x, y, color);
		y++;
	}
}

void	calc(t_data *data)
{
	int	x;
	x = 0;
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
			if (map[data->wall.map_x][data->wall.map_y] > 0) 
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

		if (map[data->wall.map_x][data->wall.map_y] > 0)
			data->wall.color = 0xFF0000;
		else
			data->wall.color = 0xFFFF00;
		
		if (data->wall.side == 1)
			data->wall.color = data->wall.color / 2;
	
		verLine(data, x, data->wall.draw_start, data->wall.draw_end, data->wall.color);
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
		// draw(data);
}

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

int	main_loop(t_data *data)
{
	render_rect(&data->img, (t_rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT/2, 0xF8F8FF});
	render_rect(&data->img, (t_rect){0, WINDOW_HEIGHT/2, WINDOW_WIDTH, WINDOW_HEIGHT/2, 0xFFFFF});
	calc(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
    int     fd;
    
	data.player.pos_x = 20;
	data.player.pos_y = 11;
	data.player.dir_x = -1;
	data.player.dir_y = 0;
	data.player.plane_x = 0;
	data.player.plane_y = 0.66;
	data.wall.moveSpeed = 1;
	data.wall.rotSpeed = 1;

	int	i = 0;
	data.wall.buf = (int **)malloc(sizeof(int *) * WINDOW_HEIGHT);
	while (i < WINDOW_HEIGHT)
	{
		data.wall.buf[i] = (int *)malloc(sizeof(int) * WINDOW_WIDTH);
		++i;
	}
	i = 0;
	int	j = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			data.wall.buf[i][j] = 0;
			++j;
		}
		++i;
	}
	while (i < 8)
	{
		j = 0;
		while (j < tex_width * tex_height)
		{
			data.wall.buf[i][j] = 0;
			++j;
		}
		++i;
	}
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
			data.wall.texture[0][tex_width * x + y] = 65536 * 254 * (x != y && x != tex_width - y); //flat red texture with black cross
			data.wall.texture[1][tex_width * x + y] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			data.wall.texture[2][tex_width * x + y] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			data.wall.texture[3][tex_width * x + y] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			data.wall.texture[4][tex_width * x + y] = 256 * xorcolor; //xor green
			data.wall.texture[5][tex_width * x + y] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			data.wall.texture[6][tex_width * x + y] = 65536 * ycolor; //red gradient
			data.wall.texture[7][tex_width * x + y] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		
			++y;
		}
		++x;
	}
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (EXIT_FAILURE);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (EXIT_FAILURE);
	}
    data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	mlx_hook(data.win_ptr, ClientMessage, LeaveWindowMask, &handle_keypress, &data); /* ADDED */
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_input, &data); /* ADDED */
	
	mlx_loop_hook(data.mlx_ptr, &main_loop, &data);
    mlx_loop(data.mlx_ptr);

	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
    mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}