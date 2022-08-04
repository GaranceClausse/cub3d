/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:07:15 by gclausse          #+#    #+#             */
/*   Updated: 2022/08/04 10:35:29 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	check_first_last_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_strtrim(str, " \n");
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
		{
			free(line);
			return (my_error("Map isn't closed"));
		}
		i++;
	}
	free(line);
	return (0);
}

int	check_empty_spaces(char **tab_map, t_mapinfo *mapinfo)
{
	int	i;
	int	j;

	i = 0;
	while (i < mapinfo->line_count)
	{
		j = 0;
		while (tab_map[i][j])
		{
			if (tab_map[i][j] == ' ')
				if ((i != 0 && tab_map[i - 1][j] && tab_map[i - 1][j] == '0')
					|| (i != mapinfo->line_count - 1
					&& tab_map[i + 1][j] && tab_map[i + 1][j] == '0')
					|| (tab_map[i][j + 1] && tab_map[i][j + 1] == 0))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_walls(char **tab_map, t_mapinfo *mapinfo)
{
	int		i;
	char	*line;

	i = 0;
	while (i < mapinfo->line_count - 1)
	{
		line = ft_strtrim(tab_map[i], " \n");
		if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
		{
			free(line);
			return (my_error("Map isn't closed"));
		}
		free(line);
		i++;
	}
	if (check_empty_spaces(tab_map, mapinfo) == 1)
		return (my_error("Wrong map"));
	return (0);
}

int	check_letters(char **tab_map)
{
	int		i;
	int		j;

	i = 0;
	while (tab_map[i] != NULL)
	{
		j = 0;
		while (tab_map[i][j] && tab_map[i][j] != '\n')
		{
			if ((tab_map[i][j] != '1' && tab_map[i][j] != '0'
				&& tab_map[i][j] != 'N' && tab_map[i][j] != 'S'
				&& tab_map[i][j] != 'E' && tab_map[i][j] != 'W'
				&& tab_map[i][j] != '\n' && tab_map[i][j] != ' ')
				)
				return (my_error("Wrong map"));
			j++;
		}
		i++;
	}
	return (0);
}

int	check_player(char **tab_map)
{
	int	i;
	int	j;
	int	player;

	i = 1;
	player = 0;
	while (tab_map[i] != NULL)
	{
		j = 0;
		while (tab_map[i][j] && tab_map[i][j] != '\n')
		{
			if (tab_map[i][j] == 'N' || tab_map[i][j] == 'S'
				||tab_map[i][j] == 'E' || tab_map[i][j] == 'W')
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		return (my_error("Map should have one player (and only one)"));
	return (0);
}
