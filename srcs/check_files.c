/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:09:29 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/27 12:21:22 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

int	verify_filename(char *mapfile)
{
	int	len;

	len = ft_strlen(mapfile);
	if (len < 5)
		return (1);
	if (mapfile[len - 4] == '.' && mapfile[len - 3] == 'c'
		&& mapfile[len - 2] == 'u' && mapfile[len - 1] == 'b')
		return (0);
	return (1);
}

static int	check_digit(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	check_colors(char *texture)
{
	int		i;
	char	*line;
	char	**color;

	i = -1;
	if (texture[0] != '\0')
	{
		color = ft_split(texture, ',');
		if (!color[0] || !color[1] || !color[2])
			return (1);
		while (++i < 3)
		{
			line = ft_strtrim(color[i], " \n");
			if (check_digit(line) || ft_atoi(line) < 0 || ft_atoi(line) > 255)
			{
				free_all(color, line);
				return (1);
			}
			free(line);
		}
		free_all(color, NULL);
		return (0);
	}
	return (1);
}

int	check_texture_files(t_textures *textinfo)
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
	else if (textinfo->dble != 0)
		return (1);
	return (0);
}
