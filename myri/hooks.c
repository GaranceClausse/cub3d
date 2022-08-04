/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:59:55 by myrmarti          #+#    #+#             */
/*   Updated: 2022/08/03 12:34:50 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	click_btn(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	return (0);
}

int	handle_release(int key, t_data *data)
{
	if (key == K_A)
		data->key_left = 0;
	else if (key == K_D)
		data->key_right = 0;
	else if (key == K_S)
		data->key_back = 0;
	else if (key == K_W)
		data->key_forward = 0;
	else if (key == XK_Right)
		data->key_r_right = 0;
	else if (key == XK_Left)
		data->key_r_left = 0;
	return (0);
}

int	handle_input(int key, t_data *data)
{
	if (key == K_A)
		data->key_left = 1;
	else if (key == K_D)
		data->key_right = 1;
	else if (key == K_S)
		data->key_back = 1;
	else if (key == K_W)
		data->key_forward = 1;
	else if (key == XK_Right)
		data->key_r_right = 1;
	else if (key == XK_Left)
		data->key_r_left = 1;
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	return (0);
}
