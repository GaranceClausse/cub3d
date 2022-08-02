#include "../include/cub.h"

/*
void	init_txt(t_data *mlx, t_img *txt, char *path)
{
	txt->img = mlx_xpm_file_to_image(mlx->mlx, path, &txt->w, &txt->h);
}

void	get_txt(t_data *mlx)
{
	init_txt(mlx, &mlx->txt.floor, FLOOR);
	init_txt(mlx, &mlx->txt.wall, WALL);
	init_txt(mlx, &mlx->txt.player, PLAYER);
	init_txt(mlx, &mlx->txt.collect, COLLECT);
	init_txt(mlx, &mlx->txt.exit, EXIT);
}

void	which_txt(char c, t_data mlx, int i, int j)
{
	if (c == '1')
		mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.txt.wall.img,
			(mlx.txt.wall.w * j), (mlx.txt.wall.h * i));
	else if (c == '0')
		mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.txt.floor.img,
			(mlx.txt.floor.w * j), (mlx.txt.floor.h * i));
	else if (c == 'P')
		mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.txt.player.img,
			(mlx.txt.player.w * j), (mlx.txt.player.h * i));
	else if (c == 'E')
		mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.txt.exit.img,
			(mlx.txt.exit.w * j), (mlx.txt.exit.h * i));
	else if (c == 'C')
		mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.txt.collect.img,
			(mlx.txt.collect.w * j), (mlx.txt.collect.h * i));
}

void	put_txt(char **tab_map, t_data mlx, t_mapinfo mapinfo)
{
	int	i;
	int	j;

	i = 0;
	while (i < mapinfo.line_count)
	{
		j = 0;
		while (j < mapinfo.line_len)
		{
			which_txt(tab_map[i][j], mlx, i, j);
			j++;
		}
		i++;
	}
}*/

// void	init_texture(t_data *data)
// {
// 	int x;
// 	int y;
// 	int xorcolor;
// 	int ycolor;
// 	int xycolor;

// 	x = -1;
// 	while (++x < tex_w)
// 	{
// 		y = -1;
// 		while (++y < tex_h)
// 		{
// 			xorcolor = (x * 256 / tex_w) ^ (y * 256 / tex_h);
// 			ycolor = y * 256 / tex_h;
// 			 xycolor = y * 128 / tex_h + x * 128 / tex_w;
// 			data->wall.texture[0][tex_w * x + y] = 65536 * 254 * (x != y && x != tex_w - y);
// 			data->wall.texture[1][tex_w * x + y] = xycolor + 256 * xycolor + 65536 * xycolor;
// 			data->wall.texture[2][tex_w * x + y] = 256 * xycolor + 65536 * xycolor;
// 			data->wall.texture[3][tex_w * x + y] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
// 			data->wall.texture[4][tex_w * x + y] = 256 * xorcolor;
// 			data->wall.texture[5][tex_w * x + y] = 65536 * 192 * (x % 16 && y % 16);
// 			data->wall.texture[6][tex_w * x + y] = 65536 * ycolor;
// 			data->wall.texture[7][tex_w * x + y] = 128 + 256 * 128 + 65536 * 128;
// 			mlx_xpm_to_image(data->mlx_ptr, )
// 		}
// 	}
// }

// void	load_image(t_data *data, int *texture, char *path, t_img *img)
// {
// 	// img = (t_img *){0};
// 	int	y = 0;
// 	int	x = 0;
// 	img->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, path, &img->width, &img->height);
// 	printf("%p\n", img->mlx_img);
// 	img->addr = (int *)mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
// 	while (y < img->height)
// 	{
// 		x = 0;
// 		while (x < img->width)
// 		{
// 			texture[img->width * y + x] = img->addr[img->width * y + x];
// 			++x;
// 		}
// 		++y;
// 	}
// 	mlx_destroy_image(data->mlx_ptr, img->mlx_img);
// }

void	load_image(t_data *data, char *path, t_img *img, int i)
{
	img->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, path, &img->width, &img->height);
	img->addr = (int *)mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
    if (!(data->wall.texture[i] = (int *)malloc(sizeof(int) * (img->height * img->width))))
		return ;
	for (int j = 0; j < img->height * img->width; j++)
	{
		data->wall.texture[i][j] = 0;
	}
    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            data->wall.texture[i][img->width * y + x] = img->addr[img->width * y + x];
        }
    }
	mlx_destroy_image(data->mlx_ptr, img->mlx_img);
}

void	load_texture(t_data *data)
{
	(void)data;
	load_image(data, "xpmfiles/southtext.xpm", &data->text, 0);
	load_image(data, "xpmfiles/southtext.xpm", &data->text, 1);
	load_image(data, "xpmfiles/southtext.xpm", &data->text, 2);
	load_image(data, "xpmfiles/southtext.xpm", &data->text, 3);
}

void	init_color_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	i = -1;
	
	while (++i < H)
	{
		j = 0;
		while (j < W)
			data->buf[i][j++] = 0;
	}
	data->wall.texture = (int **)malloc(sizeof(int *) * 4);
	load_texture(data);
}

void	init_pst(t_data *data)
{
	if (data->player.start == 'N')
	{
		data->player.dir_x = -1;
		data->player.plane_y = 0.66;
	}
	if (data->player.start == 'S')
	{
		data->player.dir_x = 1;
		data->player.plane_y = -0.66;
	}
	if (data->player.start == 'E')
	{
		data->player.dir_y = 1;
		data->player.plane_x = 0.66;

	}
	if (data->player.start == 'W')
	{
		data->player.plane_x = -0.66;
		data->player.dir_y = -1;
	}
}

void	init_vrbl(t_data *data)
{
	data->key_left = 0;
	data->key_right = 0;
	data->key_back = 0;
	data->key_forward = 0;
	data->key_r_right = 0;
	data->key_r_left = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	data->wall.moveSpeed = 0.2;
	data->wall.rotSpeed = 0.2;
	init_pst(data);
	init_color_map(data);
	return ;
}
