/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:00:19 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/27 15:21:54 by gclausse         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	int			fd;
	t_mapinfo	mapinfo;
	char		**tab_map;
	char		**file_to_parse;

	init_mapinfo(&mapinfo);
	if (argc != 2)
		return (error("two arguments needed"));
	if (verify_filename(argv[1]) != 0)
		return (error("file type should be *.cub"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (error("couldn't open the file"));
	file_to_parse = create_parsing(fd, &mapinfo);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (error("couldn't open the file"));
	tab_map = get_map(fd, file_to_parse, &mapinfo);
	print_tabmap(tab_map); // debug
	free_all(tab_map, NULL);
}
