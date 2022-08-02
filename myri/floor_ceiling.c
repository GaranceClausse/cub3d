#include "../include/cub.h"

void	init_vrbl_floor(t_data *data, t_floor *floor, int y)
{
		int p;

		p = y -H / 2;
		floor->rayDirX0 = data->player.dir_x - data->player.plane_x;
		floor->rayDirY0 = data->player.dir_y - data->player.plane_y;
		floor->rayDirX1 = data->player.dir_x + data->player.plane_x;
		floor->rayDirY1 = data->player.dir_y + data->player.plane_y;

		floor->posZ = 0.5 *H;

		floor->rowDistance = floor->posZ / p;

		floor->floorStepX = floor->rowDistance * (floor->rayDirX1 - floor->rayDirX0) / W;
		floor->floorStepY = floor->rowDistance * (floor->rayDirY1 - floor->rayDirY0) / W;

		floor->floorX = data->player.pos_x + floor->rowDistance * floor->rayDirX0;
		floor->floorY = data->player.pos_y + floor->rowDistance * floor->rayDirY0;
}

int	encode_rgb(int red, int green, int blue)
{
	// printf("red = %d, greem = %d, blue = %d", red, green, blue);
	return (red << 16 | green << 8 | blue);
}

int	get_floor_ceiling_color(char *texture)
{
	int		i;
	char	**color_trim;
	char	**color;
	int		color_int;

	i = 0;
	color_int = 0;
	color_trim = malloc(sizeof(char*) * 4);
	if (!color_trim)
		return (1);	
	color = ft_split(texture, ',');
	while (i < 3)
	{
		color_trim[i] = ft_strtrim(color[i], " \n");
		i++;
	}
	color_trim[3] = NULL;
	color_int = encode_rgb(ft_atoi(color_trim[0]), ft_atoi(color_trim[1]), ft_atoi(color_trim[2]));
	free_all(color, NULL);
	free_all(color_trim, NULL);
	return (color_int);
}

void	calc_vertical_f_c(t_data *data, t_floor *floor, int y)
{
	int color;
	int rgb_floor;
	int	rgb_sky;
	int	i;
	i = 0;
	
	rgb_floor = get_floor_ceiling_color(data->textures.floor);
	rgb_sky = get_floor_ceiling_color(data->textures.sky);
	while (i < W)
	{
		floor->cellX = (int)(floor->floorX);
		floor->cellY = (int)(floor->floorY);
		floor->tx = (int)(tex_w * (floor->floorX - floor->cellX)) & (tex_w - 1);
		floor->ty = (int)(tex_h * (floor->floorY - floor->cellY)) & (tex_h - 1);
		floor->floorX += floor->floorStepX;
		floor->floorY += floor->floorStepY;
		floor->floorTexture = 0;
		floor->ceilingTexture = 2;
		color = rgb_floor;
		color = (color >> 1) & 8355711;
		data->buf[y][i] = color;
		color = rgb_sky;
		color = (color >> 1) & 8355711;
		data->buf[H - y - 1][i] = color;
		++i;
	}
}

void	calc_floor(t_data *data)
{
	t_floor	floor;

	int	i;
	i = 0;
	while (i <H)
	{
		init_vrbl_floor(data, &floor, i);
		calc_vertical_f_c(data, &floor, i);
		++i;
	}
}
