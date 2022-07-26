/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:56:59 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/25 16:31:27 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	free_all(char **tab_map)
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
	free_all(tab_map);
	exit(EXIT_FAILURE);
}