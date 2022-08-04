/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_valid_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:12:07 by gclausse          #+#    #+#             */
/*   Updated: 2022/08/04 15:04:06 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	**replace_spaces(char **tab_map)
{
	int	i;
	int	j;

	i = 0;
	while (tab_map[i])
	{
		j = 0;
		while (tab_map[i][j])
		{
			if (tab_map[i][j] == ' ')
				tab_map[i][j] = '1';
			j++;
		}
		i++;
	}
	return (tab_map);
}

int	valid_map(char **tab_map, t_mapinfo *mapinfo, t_data *data)
{
	if (check_first_last_line(tab_map[0]) != 0
		|| check_first_last_line(tab_map[mapinfo->line_count -1]) != 0
		|| check_walls(tab_map, mapinfo) != 0
		|| check_player(tab_map) != 0
		|| check_letters(tab_map) != 0)
	{
		free_all(tab_map, NULL);
		free_textstruct(&(data->textures));
		exit (EXIT_FAILURE);
	}
	tab_map = replace_spaces(tab_map);
	return (0);
}

char	*dup_map(char *s1, int len)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = malloc(sizeof(char) * (len + 3));
	if (!cpy)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
	{
		cpy[i] = s1[i];
		i++;
	}
	if (i != 0 && s1[i - 1] == '1')
	{		
		while (i <= len)
		{
			cpy[i] = ' ';
			i++;
		}
	}
	cpy[i] = '\n';
	cpy[++i] = '\0';
	return (cpy);
}

char	**get_textures_and_map(t_data *data, char **f_parse, t_mapinfo *mapinfo)
{
	int		i;
	int		j;
	char	**tab_map;

	i = 0;
	j = 0;
	tab_map = NULL;
	if (!(check_textures(data, f_parse, mapinfo, &i)))
	{
		mapinfo->line_count -= i;
		tab_map = malloc(sizeof(char *) * ((mapinfo->line_count + 1)));
		if (!tab_map)
			void_my_error(tab_map);
		while (j < mapinfo->line_count)
		{
			tab_map[j] = dup_map(f_parse[i], mapinfo->line_len - 1);
			if (tab_map[j] == NULL)
				return ((void *) NULL);
			i++;
			j++;
		}
		tab_map[j] = NULL;
		free_all(f_parse, NULL);
	}
	return (tab_map);
}

char	**get_map(int fd, char **f_parse, t_data *data, t_mapinfo *mapinfo)
{
	int		i;
	char	**tab_map;

	f_parse[0] = my_get_next_line(fd);
	if (!f_parse[0])
	{
		free(f_parse);
		void_my_error(f_parse);
	}
	i = 1;
	while (i < mapinfo->line_count)
	{
		f_parse[i] = my_get_next_line(fd);
		i++;
	}
	f_parse[i] = NULL;
	tab_map = get_textures_and_map(data, f_parse, mapinfo);
	valid_map(tab_map, mapinfo, data);
	return (tab_map);
}
