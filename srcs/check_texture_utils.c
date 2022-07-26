/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:45:10 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/26 14:56:52 by gclausse         ###   ########.fr       */
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

void	free_textstruct(t_textures *textinfo)
{
	free(textinfo->no);
	free(textinfo->so);
	free(textinfo->we);
	free(textinfo->ea);
	free(textinfo->floor);
	free(textinfo->sky);
}

static int	check_colors(char *texture)
{
	int		i;
	int		j;
	char	*line;
	char	**color;

	i = 0;	
	color = ft_split(texture, ',');
	if (!color[0] || !color[1] || !color[2])
		return (1);
	while (i < 3)
	{
		line = ft_strtrim(color[i], " \n");
		j = 0;
		while (line[j])
		{
			if (ft_isdigit(line[j]))
			{
				free_all(color);
				free(line);
				return (1);
			}
			j++;
		}
		if (ft_atoi(line) < 0 || ft_atoi(line) > 255)
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

	fd = open(textinfo->no, O_RDONLY);
	if (fd == -1)
		return (1);
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
	if (check_colors(textinfo->sky) == 1 || check_colors(textinfo->floor) == 1)
		return (1);
	return (0);
}

void	get_texture(t_textures *textinfo, char *line, char c)
{
	char	*to_trim;

	to_trim = ft_strtrim(line, " \n");
	if (c == 'N')
		textinfo->no = ft_strdup(to_trim);
	else if (c == 'S')
		textinfo->so = ft_strdup(to_trim);
	else if (c == 'W')
		textinfo->we = ft_strdup(to_trim);
	else if (c == 'E')
		textinfo->ea = ft_strdup(to_trim);
	else if (c == 'F') //  a revoir
		textinfo->floor = ft_strdup(line);
	else if (c == 'C') // a revoir
		textinfo->sky = ft_strdup(line);
	free(to_trim);
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
				get_texture(&textinfo, &line[2], line[0]);
		free(line);
		// endroit ou recuperer les textures dans une structure
		j++;
		(*i)++;
		line = ft_strtrim(file_to_parse[j], " ");
	}
	while (file_to_parse[mapinfo->line_count - 1][0] == '\n')
		mapinfo->line_count--;
	if (check_texture_files(&textinfo) == 1) // check if there is texture!
	{
		free(line);
		error("problem with the texture files");
		free_textstruct(&textinfo);
		free_all(file_to_parse);
		exit (EXIT_FAILURE);
	}
	free(line);
	free_textstruct(&textinfo);
	return (0);
}
