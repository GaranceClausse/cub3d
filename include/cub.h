/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclausse <gclausse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:14:11 by gclausse          #+#    #+#             */
/*   Updated: 2022/08/04 15:04:26 by gclausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define W 900
# define H 860
# define TEX_H 64
# define TEX_W 64
# define WHITE_PIXEL 0xFFFFFF
# define BLACK_PIXEL 00000
# define RED_PIXEL  0xFF2F02
# define BLUE_PIXEL  0x0464F1
# define YELLOW_PIXEL 0XFFFF6B
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include "../exec/gnl/get_next_line.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# define PI 3.14159265359
# define K_A 97
# define K_D 100
# define K_S 115
# define K_W 119
# define F_D 119
# define F_G 119

typedef struct s_textures {
	int		dble;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor;
	char	*sky;
}				t_textures;

typedef struct s_mapinfo {
	int	line_count;
	int	line_len;
	int	player;
	int	exit;
	int	x;
	int	y;
}			t_mapinfo;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_rect
{
	int	x;
	int	y;
	int	color;
}	t_rect;

typedef struct s_window
{
	int	x;
	int	y;
}				t_window;

typedef struct s_image
{
	void	*background;
	void	*character;
	void	*exit;
	void	*item;
	void	*wall;
}				t_image;

typedef struct s_collect
{
	int	number_item_to_collect;
	int	exit_game;
	int	perso;
	int	item;
	int	wall;
}				t_collect;

typedef struct s_localisation
{
	int			move;
	int			character_x;
	int			character_y;
}				t_localisation;

typedef struct s_game
{
	t_localisation	loc;
	t_image			image;
	t_window		window;
	t_collect		collect;
}				t_game;

typedef struct s_floor
{
	float	ray_dir_x;
	float	ray_dir_y;
	float	ray_dir_x1;
	float	ray_dir_y1;
	float	posz;
	float	rowdistance;
	float	floor_step_x;
	float	floor_step_y;
	float	floorx;
	float	floory;
	int		cellx;
	int		celly;
	int		tx;
	int		ty;
	int		floortexture;
	int		ceilingtexture;
}				t_floor;

typedef struct s_color
{
	int		texnum;
	int		texx;
	int		y;
	int		texy;
	double	wallx;
	double	step;
	double	texpos;
}				t_color;

typedef struct s_wall_info
{
	double		movespeed;
	double		rotspeed;
	double		camera_x;
	double		raydir_x;
	double		raydir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	double		wall_x;
	double		step;
	double		tex_pos;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	int			**texture;
	int			tex_x;
	int			tex_y;
	int			color;
	int			x;
	int			y;
}				t_wall_info;

typedef struct s_player
{
	char		start;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_data
{
	int			opt;
	int			buf[H][W];
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		text;
	t_game		game;
	int			cur_img;
	int			key_forward;
	int			key_back;
	int			key_left;
	int			key_right;
	int			key_r_left;
	int			key_r_right;
	char		**tab_map;
	t_wall_info	wall;
	t_player	player;
	t_mapinfo	mapinfo;
	t_textures	textures;
}				t_data;

//Create color windows
int		main_loop(t_data *data);
void	print_map(t_data *game);
void	update_map(t_data *data);

//Free_error
void	free_map(char **map);
void	write_error(char *str);
void	map_is_wrong(char *str, char **map);

//Hooks
int		click_btn(t_data *data);
int		handle_keyrelease(int keysym, void *data);
int		handle_release(int key, t_data *data);
int		handle_input(int keysym, t_data *data);

//Floor
void	calc_floor(t_data *data);

//Movement
void	move_key(t_data *data);
void	rotate_key(t_data *data);

void	calc(t_data *data);
void	init_vrbl(t_data *data);

void	img_pix_put(t_img *img, int x, int y, int color);
int		main_loop(t_data *data);
void	draw(t_data *data);

void	trash(t_data *data);

//COLOR
void	choose_color(t_data *data, int x);

//check map utils
int		check_player(char **tab_map);
int		check_letters(char **tab_map);
int		check_first_last_line(char *line);
int		check_walls(char **tab_map, t_mapinfo *mapinfo);

//check files
int		verify_filename(char *mapfile);
int		check_texture_files(t_textures *textinfo);
//check_textures
int		check_textures(t_data *data,
			char **f_parse, t_mapinfo *mapinfo, int *i);

//get valid map
char	**create_parsing(int fd, t_mapinfo *mapinfo);
char	**get_map(int fd, char **tab_map, t_data *data, t_mapinfo *mapinfo);
int		valid_map(char **tab_map, t_mapinfo *mapinfo, t_data *data);
char	**get_textures_and_map(t_data *data,
			char **file_to_parse, t_mapinfo *mapinfo);

//errors
void	free_all(char **tab_map, char *str);
void	free_textstruct(t_textures *textinfo);
int		my_error(char *str);
void	void_my_error(char **tab_map);

//debug
void	print_tabmap(char **tab_map);

//main parsing
void	init_mapinfo(t_mapinfo *mapinfo);
int		parsing(int argc, char **argv, t_data *data);

void	verif_pst(t_data *data);

//calc_text
void	calc_opt_1(t_data *data);
void	calc_opt_2(t_data *data);
void	calc_opt_3(t_data *data);
void	calc_opt_4(t_data *data);

void	load_texture(t_data *data);

#endif