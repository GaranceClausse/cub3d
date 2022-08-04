/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:20:02 by myrmarti          #+#    #+#             */
/*   Updated: 2022/08/03 12:52:36 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	loop_color(t_data *data, t_color *select_clr, int x)
{
	int		color;
	int		y;

	y = data->wall.draw_start - 1;
	while (++y < data->wall.draw_end)
	{
		select_clr->texy = (int)select_clr->texpos & (TEX_H - 1);
		select_clr->texpos += select_clr->step;
		color = data->wall.texture[select_clr->texnum]
		[TEX_H * select_clr->texy + select_clr->texx];
		if (data->wall.side == 1)
			color = (color >> 1) & 8355711;
		data->buf[y][x] = color;
	}
}

void	choose_color(t_data *data, int x)
{
	t_color	select_clr;

	if (data->tab_map[data->wall.map_y][data->wall.map_x] == '1')
	{
		select_clr.texnum = data->opt;
	}
	else
		select_clr.texnum = 0;
	if (data->wall.side == 0)
		select_clr.wallx = data->player.pos_y
			+ data->wall.perp_wall_dist * data->wall.raydir_y;
	else
		select_clr.wallx = data->player.pos_x
			+ data->wall.perp_wall_dist * data->wall.raydir_x;
	select_clr.wallx -= floor(select_clr.wallx);
	select_clr.texx = (int)(select_clr.wallx * (double)TEX_W);
	if (data->wall.side == 0 && data->wall.raydir_x > 0)
		select_clr.texx = TEX_W - select_clr.texx - 1;
	if (data->wall.side == 1 && data->wall.raydir_y < 0)
		select_clr.texx = TEX_W - select_clr.texx - 1;
	select_clr.step = 1.0 * TEX_H / data->wall.line_height;
	select_clr.texpos = (data->wall.draw_start
			- H / 2 + data->wall.line_height / 2) * select_clr.step;
	loop_color(data, &select_clr, x);
}

void	draw(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			data->img.addr[y * W + x] = data->buf[y][x];
			++x;
		}
		++y;
	}
	if (data->mlx && data->win && data->img.img)
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

int	main_loop(t_data *data)
{
	calc(data);
	move_key(data);
	rotate_key(data);
	return (0);
}
