/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:14:11 by gclausse          #+#    #+#             */
/*   Updated: 2022/07/25 13:19:40 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

//# include "mlx_linux/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>

typedef struct s_textures {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor;
	char	*sky;
}			t_textures;

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

//check_textures
int	check_textures(char **file_to_parse, t_mapinfo *mapinfo, int *i);

//get valid map
char	**create_parsing(int fd, t_mapinfo *mapinfo);
char	**get_map(int fd, char **tab_map, t_mapinfo *mapinfo);
int		valid_map(char **tab_map, t_mapinfo *mapinfo);
char	**get_textures_and_map(char **file_to_parse, t_mapinfo *mapinfo);// ajouter structure textures

//errors
void	free_all(char **tab_map);
int		error(char *str);
void	void_error(char **tab_map);

//debug
void	print_tabmap(char **tab_map);

#endif