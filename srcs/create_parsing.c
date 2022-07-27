/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:38:03 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/27 11:59:55 by gclausse         ###   ########.fr       */
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
