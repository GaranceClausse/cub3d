/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:12:53 by myrmarti          #+#    #+#             */
/*   Updated: 2022/08/03 14:13:24 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	verif_pst(t_data *data)
{
	if (data->tab_map[(int)data->player.pos_y - 1]
		[(int)data->player.pos_x] == '1')
		data->player.pos_y += 0.5;
	else if (data->tab_map[(int)data->player.pos_y + 1]
		[(int)data->player.pos_x] == '1')
		data->player.pos_y -= 0.5;
	if (data->tab_map[(int)data->player.pos_y]
		[(int)data->player.pos_x + 1] == '1')
		data->player.pos_x -= 0.5;
	else if (data->tab_map[(int)data->player.pos_y]
		[(int)data->player.pos_x - 1] == '1')
		data->player.pos_x += 0.5;
}
