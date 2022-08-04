/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:23:35 by myrmarti          #+#    #+#             */
/*   Updated: 2022/08/03 12:51:07 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	init_vrbl_floor(t_data *data, t_floor *floor, int y)
{
	int	p;

	p = y - H / 2;
	floor->ray_dir_x = data->player.dir_x - data->player.plane_x;
	floor->ray_dir_y = data->player.dir_y - data->player.plane_y;
	floor->ray_dir_x1 = data->player.dir_x + data->player.plane_x;
	floor->ray_dir_y1 = data->player.dir_y + data->player.plane_y;
	floor->posz = 0.5 * H;
	floor->rowdistance = floor->posz / p;
	floor->floor_step_x = floor->rowdistance
		* (floor->ray_dir_x1 - floor->ray_dir_x) / W;
	floor->floor_step_y = floor->rowdistance
		* (floor->ray_dir_y1 - floor->ray_dir_y) / W;
	floor->floorx = data->player.pos_x + floor->rowdistance * floor->ray_dir_x;
	floor->floory = data->player.pos_y + floor->rowdistance * floor->ray_dir_y;
}

int	encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

int	get_floor_ceiling_color(char *texture)
{
	int		i;
	char	**color_trim;
	char	**color;
	int		color_int;

	i = 0;
	color_int = 0;
	color_trim = malloc(sizeof(char *) * 4);
	if (!color_trim)
		return (1);
	color = ft_split(texture, ',');
	while (i < 3)
	{
		color_trim[i] = ft_strtrim(color[i], " \n");
		i++;
	}
	color_trim[3] = NULL;
	color_int = encode_rgb(ft_atoi(color_trim[0]),
			ft_atoi(color_trim[1]), ft_atoi(color_trim[2]));
	free_all(color, NULL);
	free_all(color_trim, NULL);
	return (color_int);
}

void	calc_vertical_f_c(t_data *data, t_floor *floor, int y)
{
	int	color;
	int	rgb_floor;
	int	rgb_sky;
	int	i;

	i = -1;
	rgb_floor = get_floor_ceiling_color(data->textures.floor);
	rgb_sky = get_floor_ceiling_color(data->textures.sky);
	while (++i < W)
	{
		floor->cellx = (int)(floor->floorx);
		floor->celly = (int)(floor->floory);
		floor->tx = (int)(TEX_W * (floor->floorx - floor->cellx)) & (TEX_W - 1);
		floor->ty = (int)(TEX_H * (floor->floory - floor->celly)) & (TEX_H - 1);
		floor->floorx += floor->floor_step_x;
		floor->floory += floor->floor_step_y;
		floor->floortexture = 0;
		floor->ceilingtexture = 2;
		color = rgb_floor;
		data->buf[y][i] = color;
		color = rgb_sky;
		data->buf[H - y - 1][i] = color;
	}
}

void	calc_floor(t_data *data)
{
	t_floor	floor;
	int		i;

	i = 0;
	while (i < H)
	{
		init_vrbl_floor(data, &floor, i);
		calc_vertical_f_c(data, &floor, i);
		++i;
	}
}
