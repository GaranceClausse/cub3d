/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:00:17 by myrmarti          #+#    #+#             */
/*   Updated: 2022/08/04 13:15:25 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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
	if (!data->wall.texture)
		return ;
	i = 0;
	while (i < 4)
	{
		data->wall.texture[i] = 0;
		++i;
	}
	load_texture(data);
}

void	init_pst(t_data *data)
{
	if (data->player.start == 'W')
	{
		data->player.dir_x = -1;
		data->player.plane_y = 0.66;
	}
	if (data->player.start == 'E')
	{
		data->player.dir_x = 1;
		data->player.plane_y = -0.66;
	}
	if (data->player.start == 'S')
	{
		data->player.dir_y = 1;
		data->player.plane_x = 0.66;
	}
	if (data->player.start == 'N')
	{
		data->player.plane_x = -0.66;
		data->player.dir_y = -1;
	}
}

void	init_vrbl(t_data *data)
{
	data->wall.movespeed = 0.2;
	data->wall.rotspeed = 0.1;
	init_pst(data);
	init_color_map(data);
	return ;
}
