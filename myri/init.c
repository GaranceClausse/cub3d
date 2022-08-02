#include "../include/cub.h"

void	load_image(t_data *data, char *path, t_img *img, int nb_tex)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	img->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, path, &img->width, &img->height);
	img->addr = (int *)mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
    if (!(data->wall.texture[nb_tex] = (int *)malloc(sizeof(int) * (img->height * img->width))))
		return ;
	while (j < img->height * img->width)
		data->wall.texture[nb_tex][j++] = 0;
	j = 0;
    while (j < img->height)
    {
		i = -1;
        while (++i < img->width)
            data->wall.texture[nb_tex][img->width * j + i] = img->addr[img->width * j + i];
		++j;
    }
	mlx_destroy_image(data->mlx_ptr, img->mlx_img);
}

void	load_texture(t_data *data)
{
	(void)data;
	printf("%s\n", data->textures.no);
	load_image(data, data->textures.no, &data->text, 0);
	load_image(data, data->textures.so, &data->text, 1);
	load_image(data, data->textures.we, &data->text, 2);
	load_image(data, data->textures.ea, &data->text, 3);
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
