/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:38:26 by myrmarti          #+#    #+#             */
/*   Updated: 2022/08/04 11:51:31 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	add_pixel(t_data *data, t_img *img, int nb_tex)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	data->wall.texture[nb_tex] = (int *)malloc(sizeof(int)
			* (img->height * img->width));
	if (!(data->wall.texture[nb_tex]))
		return ;
	while (j < img->height * img->width)
		data->wall.texture[nb_tex][j++] = 0;
	j = 0;
	while (j < img->height)
	{
		i = -1;
		while (++i < img->width)
			data->wall.texture[nb_tex][img->width * j + i]
				= img->addr[img->width * j + i];
		++j;
	}
}

void	load_image(t_data *data, char *path, t_img *img, int nb_tex)
{
	img->img = mlx_xpm_file_to_image
		(data->mlx, path, &img->width, &img->height);
	if (!img->img)
	{
		printf("Error: Problem with the textures\n");
		trash(data);
	}
	img->addr = (int *)mlx_get_data_addr
		(img->img, &img->bpp, &img->line_len, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(data->mlx, img->img);
		trash(data);
	}
	add_pixel(data, img, nb_tex);
	mlx_destroy_image(data->mlx, img->img);
}

void	load_texture(t_data *data)
{
	load_image(data, data->textures.no, &data->text, 0);
	load_image(data, data->textures.so, &data->text, 1);
	load_image(data, data->textures.we, &data->text, 2);
	load_image(data, data->textures.ea, &data->text, 3);
}
