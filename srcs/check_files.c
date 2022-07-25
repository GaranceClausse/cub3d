/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:09:29 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/25 14:53:07 by gclausse         ###   ########.fr       */
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
