/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:16:55 by myrmarti          #+#    #+#             */
/*   Updated: 2022/08/03 12:50:52 by myrmarti         ###   ########.fr       */
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

void	calc_vertical_f_c(t_data *data, t_floor *floor, int y)
{
	int	color;
	int	i;

	i = 0;
	while (i < W)
	{
		floor->cellx = (int)(floor->floorx);
		floor->celly = (int)(floor->floory);
		floor->tx = (int)(TEX_W * (floor->floorx - floor->cellx)) & (TEX_W - 1);
		floor->ty = (int)(TEX_H * (floor->floory - floor->celly)) & (TEX_H - 1);
		floor->floorx += floor->floor_step_x;
		floor->floory += floor->floor_step_y;
		floor->floortexture = 1;
		floor->ceilingtexture = 2;
		color = data->wall.texture[floor->floortexture]
		[TEX_W * floor->ty + floor->tx];
		color = (color >> 1) & 8355711;
		data->buf[y][i] = color;
		color = data->wall.texture[floor->ceilingtexture]
		[TEX_W * floor->ty + floor->tx];
		color = (color >> 1) & 8355711;
		data->buf[H - y - 1][i] = color;
		++i;
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
