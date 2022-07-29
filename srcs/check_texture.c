/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:45:10 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/29 11:31:42 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

static void	init_textures(t_textures *textinfo)
{
	textinfo->no = "\0";
	textinfo->so = "\0";
	textinfo->we = "\0";
	textinfo->ea = "\0";
	textinfo->floor = "\0";
	textinfo->sky = "\0";
	textinfo->dble = 0;
}

void	fill_texture(t_textures *textinfo, char *line, char c)
{
	char	*to_trim;

	to_trim = ft_strtrim(line, " \n");
	if (c == 'N' && textinfo->no[0] == '\0')
		textinfo->no = ft_strdup(to_trim);
	else if (c == 'S' && textinfo->so[0] == '\0')
		textinfo->so = ft_strdup(to_trim);
	else if (c == 'W' && textinfo->we[0] == '\0')
		textinfo->we = ft_strdup(to_trim);
	else if (c == 'E' && textinfo->ea[0] == '\0')
		textinfo->ea = ft_strdup(to_trim);
	else if (c == 'F' && textinfo->floor[0] == '\0')
		textinfo->floor = ft_strdup(line);
	else if (c == 'C' && textinfo->sky[0] == '\0')
		textinfo->sky = ft_strdup(line);
	else if (c == 'N' || c == 'S' || c == 'W' || c == 'E'
		|| c == 'F' || c == 'C')
		textinfo->dble++;
	free(to_trim);
}

void	get_texture(char **file_to_parse, t_textures *textinfo, int *i)
{
	char	*line;
	int		j;

	j = 0;
	line = ft_strtrim(file_to_parse[j], " ");
	while (file_to_parse[j] && ft_isdigit(line[0]) == 1)
	{
		if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
			|| line[0] == 'C' || line[0] == 'F')
			fill_texture(textinfo, &line[2], line[0]);
		free(line);
		j++;
		(*i)++;
		line = ft_strtrim(file_to_parse[j], " ");
	}
	free(line);
}

int	check_textures(char **file_to_parse, t_mapinfo *mapinfo, int *i)
{
	t_textures	textinfo;

	init_textures(&textinfo);
	get_texture(file_to_parse, &textinfo, i);
	while (file_to_parse[mapinfo->line_count - 1][0] == '\n')
		mapinfo->line_count--;
	if (check_texture_files(&textinfo) == 1)
	{
		my_error("problem with the texture files");
		free_textstruct(&textinfo);
		free_all(file_to_parse, NULL);
		exit (EXIT_FAILURE);
	}
	free_textstruct(&textinfo);
	return (0);
}
