/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:00:19 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/30 17:26:15 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	print_tabmap(char **tab_map)
{
	int	i;

	i = 0;
	while (tab_map[i])
	{
		printf("%s", tab_map[i]);
		i++;
	}
}

void	init_mapinfo(t_mapinfo *mapinfo)
{
	mapinfo->line_count = 0;
	mapinfo->line_len = 0;
	mapinfo->player = 0;
	mapinfo->exit = 0;
	return ;
}

void	get_map_info(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->tab_map[i] != NULL)
	{
		j = 0;
		while (data->tab_map[i][j] && data->tab_map[i][j] != '\n')
		{
			if (data->tab_map[i][j] == 'N' || data->tab_map[i][j] == 'S'
				|| data->tab_map[i][j] == 'E' || data->tab_map[i][j] == 'W')
			{
				data->player.start = data->tab_map[i][j];
				data->player.pos_x = j;
				data->player.pos_y = i;
				data->tab_map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

int	parsing(int argc, char **argv, t_data *data)
{
	int			fd;
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
	data->tab_map = get_map(fd, file_to_parse, &(data->mapinfo));
	get_map_info(data);
	return (0);
}
