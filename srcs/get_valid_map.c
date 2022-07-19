/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_valid_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:12:07 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/19 17:25:24 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	**create_map(int fd, t_mapinfo *mapinfo)
{
	char	**tab_map;
	char	*line;

	tab_map = NULL;
	line = get_next_line(fd);
	if (!line || line[0] == '\0')
	{
		free(line);
		void_error(tab_map);
	}
	mapinfo->line_len = ft_strlen(line) - 1;
	while (line)
	{
		free(line);
		(mapinfo->line_count)++;
		line = get_next_line(fd);
		if ((line) && (int)(ft_strlen(line) - 1) > mapinfo->line_len)
			mapinfo->line_len = (int)(ft_strlen(line) - 1);
	}
	tab_map = malloc(sizeof(char *) * ((mapinfo->line_count + 1)));
	if (!tab_map)
		void_error(tab_map);
	return (tab_map);
}

char	**get_map(int fd, char **tab_map, t_mapinfo *mapinfo)
{
	int		i;

	tab_map[0] = get_next_line(fd);
	if (!tab_map[0])
	{
		free_all(tab_map);
		void_error(tab_map);
	}
	i = 1;
	while (i < mapinfo->line_count)
	{
		tab_map[i] = get_next_line(fd);
		i++;
	}
	tab_map[i] = NULL;
	valid_map(tab_map, mapinfo);
	return (tab_map);
}

int	valid_map(char **tab_map, t_mapinfo *mapinfo)
{
	if (check_first_last_line(tab_map[0]) != 0
		|| check_first_last_line(tab_map[mapinfo->line_count - 1]) != 0
		|| check_walls(tab_map, mapinfo) != 0
		|| check_player(tab_map) != 0
		|| check_letters(tab_map) != 0)
	{
		free_all(tab_map);
		exit (EXIT_FAILURE);
	}
	return (0);
}