/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:07:15 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/19 16:55:13 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	check_first_last_line(char *str)
{
	int	i;
	char *line;

	i = 0;
	line = ft_strtrim(str, " \n");
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1')
			return (error("Map isn't closed"));
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
				&& tab_map[i][j] != '\n')
				)
				return (error("Wrong map"));
			if (cpy[0] != '1' || cpy[len - 1] != '1')
				return (error("Walls should be made of 1"));
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
