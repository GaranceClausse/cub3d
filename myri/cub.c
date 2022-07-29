#include "../include/cub.h"

void	trash(t_data *data)
{
	if (data->mlx_ptr && data->img.mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	    mlx_destroy_display(data->mlx_ptr);
	int	i = 0;
	while (i < H)
	{
		if (data->wall.buf[i])
		free(data->wall.buf[i]);
		++i;
	}
	free(data->wall.buf);
	free(data->mlx_ptr);
	free(data->win_ptr);
}

int	init_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (EXIT_FAILURE);
	data->win_ptr = mlx_new_window(data->mlx_ptr, W, H, "My first window!");
	if (data->win_ptr == NULL)
	{
		trash(data);
		return (EXIT_FAILURE);
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, W, H);
	if (data->img.mlx_img == NULL)
	{
		trash(data);
		return (EXIT_FAILURE);
	}
	data->img.addr = (int *)mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (data->img.addr == NULL)
	{
		trash(data);
		return (EXIT_FAILURE);
	}	
	return (1);
}


int	parsing(int argc, char **argv, t_data *data)
{
	int			fd;
//	t_mapinfo	mapinfo;
	char		**tab_map;
	char		**file_to_parse;

	init_mapinfo(&(data->mapinfo));
	if (argc != 2)
		return (my_error("two arguments needed"));
	if (verify_filename(argv[1]) != 0)
		return (my_error("file type should be *.cub"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (my_error("couldn't open the file"));
	file_to_parse = create_parsing(fd, &(data->mapinfo));
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (my_error("couldn't open the file"));
	tab_map = get_map(fd, file_to_parse, &(data->mapinfo));
	print_tabmap(tab_map); // debug
	free_all(tab_map, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

    if (parsing(argc, argv, &data) == 1)
		return (1);
	init_vrbl(&data);
	if (!init_window(&data))
	{
		trash(&data);
		return (2);
	}
	mlx_loop_hook(data.mlx_ptr, &main_loop, &data);
	mlx_hook(data.win_ptr, ClientMessage, LeaveWindowMask, &handle_keypress, &data); /* ADDED */
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_input, &data); /* ADDED */
    mlx_loop(data.mlx_ptr);
	trash(&data);
	return (0);
}