/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:45:10 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/25 14:52:39 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	init_textures(t_textures *textinfo)
{
	textinfo->no = "\0";
	textinfo->so = "\0";
	textinfo->we = "\0";
	textinfo->ea = "\0";
	textinfo->floor = "\0";
	textinfo->sky = "\0";
}

void	get_texture(t_textures *textinfo, char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '.')
		i++;
	if (c == 'N' && line[i] == '.')
		textinfo->no = &line[i];
	else if (c == 'S' && line[i] == '.')
		textinfo->so = &line[i];
	else if (c == 'W' && line[i] == '.')
		textinfo->we = &line[i];
	else if (c == 'E' && line[i] == '.')
		textinfo->ea = &line[i];
	else if (c == 'F') //  a revoir
		textinfo->floor = &line[2];
	else if (c == 'C') // a revoir
		textinfo->sky = &line[2];
}

int	check_textures(char **file_to_parse, t_mapinfo *mapinfo, int *i)
{
	char		*line;
	int			j;
	t_textures	textinfo;
	(void)mapinfo;

	init_textures(&textinfo);
	j = 0;
	line = ft_strtrim(file_to_parse[j], " ");
	while (file_to_parse[j] && ft_isdigit(line[0]) == 1)
	{
		if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
			|| line[0] == 'C' || line[0] == 'F')
			get_texture(&textinfo, line, line[0]);
		free(line);
		// verifier si format textures est correct!
		line = ft_strtrim(file_to_parse[j], " ");
		// endroit ou recuperer les textures dans une structure
		j++;
		(*i)++;
	}
	//if pbm texture free(file_to_parse)
	free(line);
	return (0);
}
