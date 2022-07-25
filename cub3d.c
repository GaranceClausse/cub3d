#include "cub3d.h"

void	verLine(t_data *data, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, color);
		y++;
	}
}

void	calc(t_data *data)
{
	int	x;

	x = 0;
	puts("begin");
	while (x < WINDOW_WIDTH)
	{
		data->wall.camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
		data->wall.raydir_x = data->player.dir_x + data->player.plane_x * data->wall.camera_x;
		data->wall.raydir_y = data->player.dir_y + data->player.plane_y * data->wall.camera_x;
		

		data->wall.map_x = (int)data->game.loc.character_x;
		data->wall.map_y = (int)data->game.loc.character_y;

		printf("'%d|%d\n", data->game.loc.character_x, data->game.loc.character_y);
		data->wall.delta_dist_x = fabs(1 / data->wall.raydir_x);
		data->wall.delta_dist_y = fabs(1 / data->wall.raydir_y);
		
		data->wall.hit = 0;

		if (data->wall.raydir_x < 0)
		{
			data->wall.step_x = -1;
			data->wall.side_dist_x = (data->player.pos_x - data->wall.map_x) * data->wall.delta_dist_x;
		}
		else
		{
			data->wall.step_x = 1;
			data->wall.side_dist_x = (data->wall.map_x + 1.0 - data->player.pos_x) * data->wall.delta_dist_x;
		}
		if (data->wall.raydir_y < 0)
		{
			data->wall.step_y = -1;
			data->wall.side_dist_y = (data->player.pos_y - data->wall.map_y) * data->wall.delta_dist_y;
		}
		else
		{
			data->wall.step_y = 1;
			data->wall.side_dist_y = (data->wall.map_y + 1.0 - data->player.pos_y) * data->wall.delta_dist_y;
		}

	puts("Middle1");
		while (data->wall.hit == 0)
		{
		puts("Beg");

			//jump to next map square, OR in x-direction, OR in y-direction
			if (data->wall.side_dist_x < data->wall.side_dist_y)
			{
				data->wall.side_dist_x += data->wall.delta_dist_x;
				data->wall.map_x += data->wall.step_x;
				data->wall.side = 0;
			}
			else
			{
				data->wall.side_dist_y += data->wall.delta_dist_y;
				data->wall.map_y += data->wall.step_y;
				data->wall.side = 1;
			}
			//Check if ray has data->wall.hit a wall
			if (data->game.map[data->wall.map_x][data->wall.map_y] == '1') 
				data->wall.hit = 1;
		puts("end");
		}
	puts("Middle2");
		if (data->wall.side == 0)
			data->wall.perp_wall_dist = (data->wall.map_x - data->player.pos_x + (1 - data->wall.step_x) / 2) / data->wall.raydir_x;
		else
			data->wall.perp_wall_dist = (data->wall.map_y - data->player.pos_y + (1 - data->wall.step_y) / 2) / data->wall.raydir_y;

		// WINDOW_HEIGHT of line to draw on screen
		data->wall.line_height = (int)(WINDOW_HEIGHT / data->wall.perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		data->wall.draw_start = -data->wall.line_height / 2 + WINDOW_HEIGHT / 2;
		if(data->wall.draw_start < 0)
			data->wall.draw_start = 0;
		data->wall.draw_end = data->wall.line_height / 2 + WINDOW_HEIGHT / 2;
		if(data->wall.draw_end >= WINDOW_HEIGHT)
			data->wall.draw_end = WINDOW_HEIGHT - 1;

		if (data->game.map[data->wall.map_y][data->wall.map_x] == '1')
			data->wall.color = 0xFF0000;
		else
			data->wall.color = 0xFFFF00;
		
		if (data->wall.side == 1)
			data->wall.color = data->wall.color / 2;
	puts("Middle3");

		verLine(data, x, data->wall.draw_start, data->wall.draw_end, data->wall.color);
		
		x++;
	}
}

int	main_loop(t_data *data)
{
	calc(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
    int     fd;
    
	data.player.pos_x = 12;
	data.player.pos_y = 5;
	data.player.dir_x = -1;
	data.player.dir_y = 0;
	data.player.plane_x = 0;
	data.player.plane_y = 0.66;
	data.wall.moveSpeed = 1;
	data.wall.rotSpeed = 0.05;

    if (ac != 2)
        return 2;
	//Open fd
    fd = open(av[1], O_RDONLY);
	//Get map to char **
    get_map(fd, &data.game);
    close(fd);
	//init windows
	render(&data);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (EXIT_FAILURE);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (EXIT_FAILURE);
	}
	//Create background and character
    data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	//Loop about keypress and mouvements
	mlx_loop_hook(data.mlx_ptr, &main_loop, &data);
	mlx_hook(data.win_ptr, ClientMessage, LeaveWindowMask, &handle_keypress, &data); /* ADDED */
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_input, &data); /* ADDED */
	
    mlx_loop(data.mlx_ptr);

	//Close windows
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
    mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}