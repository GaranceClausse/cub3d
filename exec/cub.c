/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myrmarti <myrmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:15:46 by myrmarti          #+#    #+#             */
/*   Updated: 2022/08/04 14:55:17 by myrmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	trash(t_data *data)
{
	int	i;

	i = 0;
	if (data->mlx && data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	while (i < 4)
	{
		if (data->wall.texture[i])
			free(data->wall.texture[i]);
		++i;
	}
	if (data->wall.texture)
		free(data->wall.texture);
	if (data->mlx)
		free(data->mlx);
	if (data->win)
		free(data->win);
	free_textstruct(&(data->textures));
	free_all(data->tab_map, NULL);
	exit(2);
}

int	init_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, W, H, "Try to escape!");
	if (data->win == NULL)
	{
		trash(data);
		return (EXIT_FAILURE);
	}
	data->img.img = mlx_new_image(data->mlx, W, H);
	if (data->img.img == NULL)
	{
		trash(data);
		return (EXIT_FAILURE);
	}
	data->img.addr = (int *)mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (data->img.addr == NULL)
	{
		trash(data);
		return (EXIT_FAILURE);
	}	
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){0};
	if (parsing(argc, argv, &data) == 1)
		return (1);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		return (1);
	init_vrbl(&data);
	if (!init_window(&data))
	{
		trash(&data);
		return (2);
	}
	mlx_loop_hook(data.mlx, &main_loop, &data);
	mlx_hook(data.win, ClientMessage, LeaveWindowMask, &click_btn, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &handle_input, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &handle_release, &data);
	mlx_loop(data.mlx);
	trash(&data);
	return (0);
}
