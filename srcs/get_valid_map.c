/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_valid_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:12:07 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/25 12:27:07 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	**create_parsing(int fd, t_mapinfo *mapinfo)
{
	char	**file_to_parse;
	char	*line;
	
	file_to_parse = NULL;
	line = get_next_line(fd);
	if (!line || line[0] == '\0')
	{
		free(line);
		void_error(file_to_parse);
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
	file_to_parse = malloc(sizeof(char *) * ((mapinfo->line_count + 1)));
	if (!file_to_parse)
		void_error(file_to_parse);
	return (file_to_parse);
}

char	**get_textures_and_map(char **file_to_parse, t_mapinfo *mapinfo) // ajouter structure textures
{
	int		i;
	int		j;
	char	*line;
	char	**tab_map;

	i = 0;
	j = 0;
	tab_map = NULL;
	line = ft_strtrim(file_to_parse[i], " ");
	while (file_to_parse[i] && ft_isdigit(line[0]) == 1)
	{
		free(line);
		line = ft_strtrim(file_to_parse[i], " ");
		// endroit ou recuperer les textures dans une structure
		i++;
	}
	//if pbm texture free(file_to_parse)	
	free(line);
	mapinfo->line_count -= i;
	tab_map = malloc(sizeof(char *) * ((mapinfo->line_count + 1)));
	if (!tab_map)
		void_error(tab_map); // checker s'il y a pas double free
	i -= 1;
	while (file_to_parse[i])
	{
		tab_map[j] = file_to_parse[i];
		i++;
		j++;
	}
	tab_map[j] = NULL;
	free(file_to_parse);
	return (tab_map);
	
}

char	**get_map(int fd, char **file_to_parse, t_mapinfo *mapinfo)
{
	int		i;
	char	**tab_map;

	file_to_parse[0] = get_next_line(fd);
	if (!file_to_parse[0])
	{
		free_all(file_to_parse);
		void_error(file_to_parse);
	}
	i = 1;
	while (i < mapinfo->line_count)
	{
		file_to_parse[i] = get_next_line(fd);
		i++;
	}
	file_to_parse[i] = NULL;
	tab_map = get_textures_and_map(file_to_parse, mapinfo);
	valid_map(tab_map, mapinfo);
	return (tab_map);
}

char	**replace_spaces(char **tab_map)
{
	int	i;
	int	j;

	i = 0;
	while(tab_map[i])
	{
		j = 0;
		while(tab_map[i][j])
		{
			if (tab_map[i][j] == ' ')
				tab_map[i][j] = '1';
			j++;
		}
		i++;
	}
	return (tab_map);
}

int	valid_map(char **tab_map, t_mapinfo *mapinfo)
{
	if (check_first_last_line(tab_map[0]) != 0
		|| check_first_last_line(tab_map[mapinfo->line_count]) != 0
		|| check_walls(tab_map, mapinfo) != 0
		|| check_player(tab_map) != 0
		|| check_letters(tab_map) != 0)
	{
		free_all(tab_map);
		exit (EXIT_FAILURE);
	}
	tab_map = replace_spaces(tab_map);
	return (0);
}