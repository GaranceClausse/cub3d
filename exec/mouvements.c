/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:05:04 by myrmarti          #+#    #+#             */
/*   Updated: 2022/08/03 12:53:29 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	rotate_vector(t_data *data, int angle)
{
	t_player	*player;
	int			tmp_x;

	player = &data->player;
	tmp_x = (player->dir_x * cos(angle)) - (player->dir_y * sin(angle));
	player->dir_y = (player->dir_x * sin(angle)) + (player->dir_y * cos(angle));
	player->dir_x = tmp_x;
}

void	mov_vertical(t_data *data)
{
	double	*pos_y;
	double	*pos_x;
	double	*dir_y;
	double	*dir_x;

	pos_y = &data->player.pos_y;
	pos_x = &data->player.pos_x;
	dir_y = &data->player.dir_y;
	dir_x = &data->player.dir_x;
	if (data->key_forward == 1)
	{
		if (data->tab_map[(int)(*pos_y + *dir_y * 0.2)][(int)(*pos_x)] == '0')
			*pos_y += *dir_y * 0.1;
		if (data->tab_map[(int)(*pos_y)][(int)(*pos_x + *dir_x * 0.2)] == '0')
			*pos_x += *dir_x * 0.1;
	}
	if (data->key_back == 1)
	{
		if (data->tab_map[(int)(*pos_y - *dir_y * 0.2)][(int)(*pos_x)] == '0')
			*pos_y -= *dir_y * 0.1;
		if (data->tab_map[(int)(*pos_y)][(int)(*pos_x - *dir_x * 0.2)] == '0')
			*pos_x -= *dir_x * 0.1;
	}
}

void	mov_horizon(t_data *data)
{
	double	*pos_y;
	double	*pos_x;
	double	*dir_y;
	double	*dir_x;

	pos_y = &data->player.pos_y;
	pos_x = &data->player.pos_x;
	dir_y = &data->player.dir_y;
	dir_x = &data->player.dir_x;
	if (data->key_left == 1)
	{
		if (data->tab_map[(int)(*pos_y + *dir_x * 0.2)][(int)(*pos_x)] == '0')
			*pos_y += *dir_x * 0.1;
		if (data->tab_map[(int)(*pos_y)][(int)(*pos_x - *dir_y * 0.2)] == '0')
			*pos_x -= *dir_y * 0.1;
	}
	if (data->key_right == 1)
	{
		if (data->tab_map[(int)(*pos_y - *dir_x * 0.2)][(int)(*pos_x)] == '0')
			*pos_y -= *dir_x * 0.1;
		if (data->tab_map[(int)(*pos_y)][(int)(*pos_x + *dir_y * 0.2)] == '0')
			*pos_x += *dir_y * 0.1;
	}
}

void	move_key(t_data *data)
{
	mov_vertical(data);
	mov_horizon(data);
}

void	rotate_key(t_data *data)
{
	double	old_dirx;
	double	old_planex;
	int		opt;

	opt = 1;
	if (data->key_r_left == 1 || data->key_r_right == 1)
	{
		if (data->key_r_left == 1)
			opt = -1;
		old_dirx = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(-data->wall.rotspeed
				* opt) - data->player.dir_y * sin(-data->wall.rotspeed * opt);
		data->player.dir_y = old_dirx * sin(-data->wall.rotspeed * opt)
			+ data->player.dir_y * cos(-data->wall.rotspeed * opt);
		old_planex = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(-data->wall.rotspeed
				* opt) - data->player.plane_y * sin(-data->wall.rotspeed * opt);
		data->player.plane_y = old_planex * sin(-data->wall.rotspeed * opt)
			+ data->player.plane_y * cos(-data->wall.rotspeed * opt);
	}
}
