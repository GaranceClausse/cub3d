#ifndef CUB3D_H
# define CUB3D_H

#define W 900
#define H 860
#define tex_h 64
#define tex_w 64
#define mapWidth 24
#define mapHeight 24

#define WHITE_PIXEL 0xFFFFFF
#define BLACK_PIXEL 00000
# define RED_PIXEL  0xFF2F02
# define BLUE_PIXEL  0x0464F1
#define YELLOW_PIXEL 0XFFFF6B


#include <X11/keysym.h>
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"
# include <math.h>
# define PI 3.14159265359

# define K_A 97
# define K_D 100
# define K_S 115
# define K_W 119
# define F_D 119
# define F_G 119


typedef struct s_img
{
	void	*mlx_img;
	int	*addr;

	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
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
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	float	posZ;
	float	rowDistance;
	float	floorStepX;
	float	floorStepY;
	float	floorX;
	float	floorY;
	int		cellX;
	int		cellY;
	int		tx;
	int		ty;
	int		floorTexture;
	int		ceilingTexture;
}				t_floor;

typedef struct s_color
{
	int texNum;
	int texX;
	int y;
	int texY;
	double wallX;
	double step;
	double texPos;
}				t_color;

typedef struct		s_wall_info
{
	double		moveSpeed;
	double		rotSpeed;
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
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	int		tex_x;
	int		tex_y;
	int		color;
	int		x;
	int		y;
	int		**buf;
	int		texture[8][tex_h * tex_w];
}			t_wall_info;

typedef struct		s_player
{
	char		start;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}			t_player;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
    t_game  game;
	int		cur_img;
	t_wall_info wall;
	t_player 	player;
}	t_data;

//Create color windows
int	main_loop(t_data *data);
void	get_map(int fd, t_game *game);
void	print_map(t_data *game);
void	update_map(t_data *data);

//Free_error
void	free_map(char **map);
void	write_error(char *str);
void	map_is_wrong(char *str, char **map);

//Hooks
int	handle_keypress(t_data *data);
int	handle_keyrelease(int keysym, void *data);
int	handle_input(int keysym, t_data *data);

//Floor
void	calc_floor(t_data *data);

//Movement
void	move_key(int key, t_data *data);
void	rotate_key(int key, t_data *data);



void	calc(t_data *data);
void	init_vrbl(t_data *data);

void	img_pix_put(t_img *img, int x, int y, int color);
int	main_loop(t_data *data);
void	draw(t_data *data);

void	trash(t_data *data);

//COLOR
void	choose_color(t_data *data, int x);

#endif