/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:07:15 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/25 12:27:25 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	check_first_last_line(char *str)
{
	int	i;
	char *line;

	i = 0;
	line = ft_strtrim(str, " \n");
	if (!line)
		return 1;
	while (line[i])
	{
		if (line[i] != '1')
		{
			free(line);
			return (error("Map isn't closed 1"));
		}
		i++;
	}
	free(line);
	return (0);
}

int	check_walls(char **tab_map, t_mapinfo *mapinfo) // check if line starts with 1, stiil need to check up and down
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
			return (error("Map isn't closed"));
		}
		free(line);
		i++;
	}	
	return (0);
}

int	check_letters(char **tab_map)
{
	int	i;
	int	j;
	int	len;
	char	*cpy;

	i = 0;
	while (tab_map[i] != NULL)
	{
		j = 0;
		cpy = ft_strtrim(tab_map[i], " \n");
		len = ft_strlen(cpy);
		while (tab_map[i][j] && tab_map[i][j] != '\n')
		{
			if ((tab_map[i][j] != '1' && tab_map[i][j] != '0'
				&& tab_map[i][j] != 'N' && tab_map[i][j] != 'S'
				&& tab_map[i][j] != 'E' && tab_map[i][j] != 'W'
				&& tab_map[i][j] != '\n' && tab_map[i][j] != ' ')
				)
			
			{
				free(cpy);
				return (error("Wrong map"));
			}
			if (cpy[0] != '1' || cpy[len - 1] != '1')
			{
				free(cpy);
				return (error("Walls should be made of 1"));
			}
			j++;
		}
		free(cpy);
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
				||tab_map[i][j] == 'E' ||tab_map[i][j] == 'W')
				player++;
			j++;
		}
		i++;
	}
	if (player != 1)
		return (error("Map should have one player (and only one)"));
	return (0);
}