/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:45:10 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/25 17:04:23 by gclausse         ###   ########.fr       */
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
}

static int	check_colors(t_textures *textinfo)
{
	int		i;
	char	*line;
	char	**color;

	i = 0;
	line = ft_strtrim(textinfo->floor, " \n");
	color = ft_split(line, ',');
	if (!color[0] || !color[1] || !color[2])
		return (1);
	while (i < 3)
	{
		if (ft_atoi(color[i]) < 0 || ft_atoi(color[i]) > 255)
		{
			free_all(color);
			free(line);
			return (1);
	}
		i++;
	}
	free_all(color);
	free(line);
	return (0);
}

static int	check_texture_files(t_textures *textinfo)
{
	int	fd;

	fd = open("./srcs/check_files.c", O_RDONLY);
	if (fd == -1)
	{
		printf("%s", textinfo->no);
		return (1);
	}
	close(fd);
	fd = open(textinfo->so, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(textinfo->we, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	fd = open(textinfo->ea, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	printf("ici cest good");
	if (check_colors(textinfo) == 1)
		return (1);
	return (0);
}

void	get_texture(t_textures *textinfo, char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '.')
		i++;
	if (c == 'N' && line[i] == '.')
		textinfo->no = ft_strdup(&line[i]);
	else if (c == 'S' && line[i] == '.')
		textinfo->so = ft_strdup(&line[i]);
	else if (c == 'W' && line[i] == '.')
		textinfo->we = ft_strdup(&line[i]);
	else if (c == 'E' && line[i] == '.')
		textinfo->ea = ft_strdup(&line[i]);
	else if (c == 'F') //  a revoir
		textinfo->floor = ft_strdup(&line[2]);
	else if (c == 'C') // a revoir
		textinfo->sky = ft_strdup(&line[2]);
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
		if (check_texture_files(&textinfo) == 1)
		{
			error("problem with the texture files");
			//penser a free la structure de textures
			free_all(file_to_parse);
			exit (EXIT_FAILURE);
		}
		// verifier si format ciel et sol est correct!
		line = ft_strtrim(file_to_parse[j], " ");
		// endroit ou recuperer les textures dans une structure
		j++;
		(*i)++;
	}
	//if pbm texture free(file_to_parse)
	free(line);
	return (0);
}
