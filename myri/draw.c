#include "../include/cub.h"

void	loop_color(t_data *data, t_color *select_clr, int x)
{
	int		color;
	int		y;

	y = data->wall.draw_start - 1;
	while (++y < data->wall.draw_end)
	{
		select_clr->texY = (int)select_clr->texPos & (tex_h - 1);
		select_clr->texPos += select_clr->step;
		color = data->wall.texture[select_clr->texNum][tex_h * select_clr->texY + select_clr->texX];
		if (data->wall.side == 1)
			color = (color >> 1) & 8355711;
		data->buf[y][x] = color;
	}
}

void	choose_color(t_data *data, int x)
{
	t_color select_clr;

	if (data->tab_map[data->wall.map_y][data->wall.map_x] == '1')
		select_clr.texNum = 1;		
	else
		select_clr.texNum = 0;
	if (data->wall.side == 0)
		select_clr.wallX = data->player.pos_y + data->wall.perp_wall_dist * data->wall.raydir_y;
	else
		select_clr.wallX = data->player.pos_x + data->wall.perp_wall_dist * data->wall.raydir_x;
	select_clr.wallX -= floor(select_clr.wallX);
	select_clr.texX = (int)(select_clr.wallX * (double)tex_w);
	if (data->wall.side == 0 && data->wall.raydir_x > 0)
		select_clr.texX = tex_w - select_clr.texX - 1;
	if (data->wall.side == 1 && data->wall.raydir_y < 0)
		select_clr.texX = tex_w - select_clr.texX - 1;
	select_clr.step = 1.0 * tex_h / data->wall.line_height;
	select_clr.texPos = (data->wall.draw_start - H / 2 + data->wall.line_height / 2) * select_clr.step;
	loop_color(data, &select_clr, x);
}


void	draw(t_data *data)
{
	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			data->img.addr[y * W + x] = data->buf[y][x];
		}
	}
	if (data->mlx_ptr && data->win_ptr && data->img.mlx_img)
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}

int	main_loop(t_data *data)
{
	calc(data);
	move_key(data);
	rotate_key(data);
	return (0);
}