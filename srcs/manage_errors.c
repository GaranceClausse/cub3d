/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:56:59 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/27 12:21:44 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	free_textstruct(t_textures *textinfo)
{
	if (textinfo->no[0] != '\0')
		free(textinfo->no);
	if (textinfo->so[0] != '\0')
		free(textinfo->so);
	if (textinfo->we[0] != '\0')
		free(textinfo->we);
	if (textinfo->ea[0] != '\0')
		free(textinfo->ea);
	if (textinfo->floor[0] != '\0')
		free(textinfo->floor);
	if (textinfo->sky[0] != '\0')
		free(textinfo->sky);
}

void	free_all(char **tab_map, char *str)
{
	int	i;

	i = 0;
	if (tab_map)
	{
		while (tab_map[i])
		{
			free (tab_map[i]);
			i++;
		}
		free(tab_map);
	}
	if (str)
		free(str);
}

int	error(char *str)
{
	write(2, "Error : \n", 8);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

void	void_error(char **tab_map)
{
	perror("Error :");
	free_all(tab_map, NULL);
	exit(EXIT_FAILURE);
}
