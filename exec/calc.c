/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:20:40 by myrmarti          #+#    #+#             */
/*   Updated: 2022/08/04 14:14:49 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	calc_init(t_data *data, int x)
{
	data->wall.camera_x = 2 * x / (double)W - 1;
	data->wall.raydir_x = data->player.dir_x + data->player.plane_x
		* data->wall.camera_x;
	data->wall.raydir_y = data->player.dir_y + data->player.plane_y
		* data->wall.camera_x;
	data->wall.map_x = (int)data->player.pos_x;
	data->wall.map_y = (int)data->player.pos_y;
	data->wall.delta_dist_x = fabs(1 / data->wall.raydir_x);
	data->wall.delta_dist_y = fabs(1 / data->wall.raydir_y);
	data->wall.hit = 0;
}

void	calc_step_side(t_data *data)
{
	if (data->wall.raydir_x < 0)
	{
		data->wall.step_x = -1;
		data->wall.side_dist_x = (data->player.pos_x
				- data->wall.map_x) * data->wall.delta_dist_x;
	}
	else
	{
		data->wall.step_x = 1;
		data->wall.side_dist_x = (data->wall.map_x
				+ 1.0 - data->player.pos_x) * data->wall.delta_dist_x;
	}
	if (data->wall.raydir_y < 0)
	{
		data->wall.step_y = -1;
		data->wall.side_dist_y = (data->player.pos_y
				- data->wall.map_y) * data->wall.delta_dist_y;
	}
	else
	{
		data->wall.step_y = 1;
		data->wall.side_dist_y = (data->wall.map_y
				+ 1.0 - data->player.pos_y) * data->wall.delta_dist_y;
	}
}

void	calc_dda(t_data *data)
{
	while (data->wall.hit == 0)
	{
		if (data->wall.side_dist_x < data->wall.side_dist_y)
		{
			calc_opt_1(data);
			data->wall.side_dist_x += data->wall.delta_dist_x;
			data->wall.map_x += data->wall.step_x;
			data->wall.side = 0;
		}
		else
		{
			calc_opt_2(data);
			data->wall.side_dist_y += data->wall.delta_dist_y;
			data->wall.map_y += data->wall.step_y;
			data->wall.side = 1;
		}
		if (data->tab_map[data->wall.map_y][data->wall.map_x] == '1')
		{
			data->wall.hit = 1;
		}
	}
	if (data->opt >= 4)
		data->opt = 0;
}

void	calc_l_length(t_data *data)
{
	if (data->wall.side == 0)
	{
		if (data->wall.raydir_x < 0)
			calc_opt_3(data);
		data->wall.perp_wall_dist = (data->wall.map_x - data->player.pos_x
				+ (1 - data->wall.step_x) / 2) / data->wall.raydir_x;
	}
	else
	{
		if (data->wall.raydir_y < 0)
			calc_opt_4(data);
		data->wall.perp_wall_dist = (data->wall.map_y - data->player.pos_y
				+ (1 - data->wall.step_y) / 2) / data->wall.raydir_y;
	}
	data->wall.line_height = (int)(H / data->wall.perp_wall_dist);
	data->wall.draw_start = -data->wall.line_height / 2 + H / 2;
	if (data->wall.draw_start < 0)
		data->wall.draw_start = 0;
	data->wall.draw_end = data->wall.line_height / 2 + H / 2;
	if (data->wall.draw_end >= H)
		data->wall.draw_end = H - 1;
}

void	calc(t_data *data)
{
	int	x;

	x = 0;
	calc_floor(data);
	while (x < W)
	{
		calc_init(data, x);
		calc_step_side(data);
		calc_dda(data);
		calc_l_length(data);
		choose_color(data, x);
		x++;
	}
	draw(data);
}
