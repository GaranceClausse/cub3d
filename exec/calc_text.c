/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:19:40 by myrmarti          #+#    #+#             */
/*   Updated: 2022/08/04 14:52:14 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	calc_opt_1(t_data *data)
{
	if (data->player.start == 'E')
		data->opt = 3;
	else if (data->player.start == 'N')
		data->opt = 2;
	else if (data->player.start == 'W')
		data->opt = 3;
	else if (data->player.start == 'S')
		data->opt = 2;
}

void	calc_opt_2(t_data *data)
{
	if (data->player.start == 'E')
		data->opt = 0;
	else if (data->player.start == 'N')
		data->opt = 1;
	else if (data->player.start == 'W')
		data->opt = 0;
	else if (data->player.start == 'S')
		data->opt = 1;
}

void	calc_opt_3(t_data *data)
{
	if (data->player.start == 'E')
		data->opt = 2;
	else if (data->player.start == 'N')
		data->opt = 3;
	else if (data->player.start == 'W')
		data->opt = 2;
	else if (data->player.start == 'S')
		data->opt = 3;
}

void	calc_opt_4(t_data *data)
{
	if (data->player.start == 'E')
		data->opt = 1;
	else if (data->player.start == 'N')
		data->opt = 0;
	else if (data->player.start == 'W')
		data->opt = 1;
	else if (data->player.start == 'S')
		data->opt = 0;
}
