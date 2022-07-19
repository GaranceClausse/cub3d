/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:14:11 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/19 17:25:36 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

//# include "mlx_linux/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>


typedef struct s_mapinfo {
	int	line_count;
	int	line_len;
	int	player;
	int	exit;
	int	x;
	int	y;
}			t_mapinfo;


//check map utils
int		check_player(char **tab_map);
int		check_letters(char **tab_map);
int		check_first_last_line(char *line);
int		check_walls(char **tab_map, t_mapinfo *mapinfo);

//check files
int		verify_filename(char *mapfile);
//int		check_textures(void);

//get valid map
char	**create_map(int fd, t_mapinfo *mapinfo);
char	**get_map(int fd, char **tab_map, t_mapinfo *mapinfo);
int		valid_map(char **tab_map, t_mapinfo *mapinfo);

//errors
void	free_all(char **tab_map);
int		error(char *str);
void	void_error(char **tab_map);

#endif