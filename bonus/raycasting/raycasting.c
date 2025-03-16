#include "../../cub3d.h"

int	no_walls(float ray_x, float ray_y, char **map)
{
	float	margin;
	int		x;
	int		y;

	margin = 10.0;
	x = ray_x / 50;
	y = ray_y / 50;
	if (map[y][x] == '1' || map[y][x] == 'D')
		return (0);
	if (map[(int)((ray_y - margin) / 50)][x] == '1' || map[(int)((ray_y
				- margin) / 50)][x] == 'D')
		return (0);
	if (map[(int)((ray_y + margin) / 50)][x] == '1' || map[(int)((ray_y
				+ margin) / 50)][x] == 'D')
		return (0);
	if (map[y][(int)((ray_x - margin) / 50)] == '1' || map[y][(int)((ray_x
				- margin) / 50)] == 'D')
		return (0);
	if (map[y][(int)((ray_x + margin) / 50)] == '1' || map[y][(int)((ray_x
				+ margin) / 50)] == 'D')
		return (0);
	return (1);
}

void	ft_init_text(t_jeux *jeux, t_cub3d *game,void *mlx)
{
	char *text[4]= {game->ea_texture, game->so_texture, game->no_texture, game->we_texture};
	char *cl = "texture/cl.xpm";
	char *pl = "texture/color_floor.xpm";
	int i = 0;

	if (!mlx)
		return_error("mlx non initialisé !");
	while(i < 4)
	{
		game->texture[i].img = mlx_xpm_file_to_image(mlx,text[i],&game->texture[i].width,&game->texture[i].height);
		if(!game->texture[i].img)
		{
			return_free_error("Ivalid Texture image", game);
			mlx_destroy_display(jeux->mlx);
		}
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,&game->texture[i].bpp, &game->texture[i].size_line, &game->texture[i].endian);
		i++;
	}	
	game->txt_plat.img = mlx_xpm_file_to_image(mlx, pl, &game->txt_plat.width, &game->txt_plat.height);
	game->txt_plat.addr = mlx_get_data_addr(game->txt_plat.img, &game->txt_plat.bpp, &game->txt_plat.size_line, &game->txt_plat.endian);
	game->txt_ciel.img = mlx_xpm_file_to_image(mlx, cl, &game->txt_ciel.width, &game->txt_ciel.height);
	if(!game->txt_plat.img || !game->txt_ciel.img)
		return_free_error("Ivalid Texture image", game);
	game->txt_ciel.addr = mlx_get_data_addr(game->txt_ciel.img, &game->txt_ciel.bpp, &game->txt_ciel.size_line, &game->txt_ciel.endian);
}

void	ft_init_r(t_jeux *game, float start, float *cos_angle, float *sin_angle,
		float *fb_x, float *fb_y, float *ray_x, float *ray_y)
{
	*cos_angle = cos(start);
	*sin_angle = sin(start);
	*fb_x = fabs(1 / *cos_angle);
	*fb_y = fabs(1 / *sin_angle);
	*ray_x = game->cub.player.player_x;
	*ray_y = game->cub.player.player_y;
}

float	ft_calc_distan(t_jeux *game, float *ray_x, float *ray_y, float cos_angle, float sin_angle)
{
	float	distance;
	int		map_x;
	int		map_y;

	distance = 0;
	while (1)
	{
		map_x = (int)(*ray_x / 50);
		map_y = (int)(*ray_y / 50);
		
		if (map_x < 0 || map_y < 0 || map_x >= WIDTH || map_y >= HEIGHT) 
			break ;
		if (game->cub.cub_map[map_y][map_x] == '1' || game->cub.cub_map[map_y][map_x] == 'D')
			break ;
		*ray_x += cos_angle;
		*ray_y += sin_angle;
		distance++;
	}
	return (distance);
}

void	ft_algo(float cos_angle, float sin_angle, int *march_x, int *march_y,
		float *ch_x, float *ch_y, int *cast_x, int *cast_y, float player_x,
		float player_y)
{
	if (cos_angle < 0) 
	{
		*march_x = -1;
		*ch_x = (player_x - *cast_x) * fabs(1 / cos_angle);
	} 
	else 
	{
		*march_x = 1;
		*ch_x = (*cast_x + 1 - player_x) * fabs(1 / cos_angle);
	}	
	if (sin_angle < 0) {
		*march_y = -1;
		*ch_y = (player_y - *cast_y) * fabs(1 / sin_angle);
	} 
	else 
	{
		*march_y = 1;
		*ch_y = (*cast_y + 1 - player_y) * fabs(1 / sin_angle);
	}
}

void perform_dda(int *cast_x, int *cast_y, float *ch_x, float *ch_y, float fb_x, float fb_y, int march_x, int march_y, int *is_vertical_hit, char **cub_map)
{
	int map_x;
	int map_y;

	while (1)
	{
		map_x = (int)(*cast_x / 50);
		map_y = (int)(*cast_y / 50);
		
		if (map_x < 0 || map_y < 0 || map_x >= WIDTH || map_y >= HEIGHT) 
			break ;
		if (cub_map[map_y][map_x] == '1' || cub_map[map_y][map_x] == 'D')
			break ;
		if (*ch_x < *ch_y) 
		{
			*ch_x += fb_x;
			*cast_x += march_x;
			*is_vertical_hit = 1;
		}
		else 
		{
			*ch_y += fb_y;
			*cast_y += march_y;
			*is_vertical_hit = 0;
		}
		if (*ch_x > 10000 || *ch_y > 10000) 
			break;
	}
}

void ft_soll(t_jeux *game, int i, int dbt_pxl)
{
	int y;
	int txt_x;
	int txt_y;
	int coll;

	y = 0;
	while (y < dbt_pxl) 
	{
		txt_x = (i * game->cub.txt_ciel.width) / WIDTH;
		txt_y = (y * game->cub.txt_ciel.height) / (HEIGHT / 2);
		
		coll = *(int *)(game->cub.txt_ciel.addr 
					+ (txt_y * game->cub.txt_ciel.size_line + txt_x * (game->cub.txt_ciel.bpp / 8)));
		
		*(int *)(game->data + (y * game->size_line + i * (game->bpp / 8))) = coll;
		y++;
	}
}

void	ft_coord(int is_vertical_hit, int march_x, int march_y, float ray_x, float ray_y, int *txt_i, int *txt_x, t_jeux *game)
{
	float impact_x;
	int map_x;
	int map_y;

	map_x = (int)(ray_x / 50);
	map_y = (int)(ray_y / 50);

	if (map_y > 0 && map_x > 0 && map_y < game->cub.map_width && map_x < game->cub.map_heigh && game->cub.cub_map[map_y][map_x] == 'D')
			{
//				printf("6666666666666666666666666666666666\n");
				*txt_i = 4;
			}
	else if (is_vertical_hit)
	{
		if (march_x == 1)
			*txt_i = 0; // mure est
		else
			*txt_i = 1; // mure ouest
	}  
	else 
	{
		if (march_y == 1)
			*txt_i = 2; // mure sude
		else
			*txt_i = 3; // mure nord
	}
	if (is_vertical_hit)
		impact_x = ray_y;
	else
		impact_x = ray_x;
	impact_x = fmod(impact_x, 50);
	*txt_x = (int)((impact_x / 50.0) * (game->cub.texture[*txt_i].width - 1));
	if (*txt_x < 0) 
		*txt_x = 0;
	if (*txt_x >= game->cub.texture[*txt_i].width) 
		*txt_x = game->cub.texture[*txt_i].width - 1;
}

void	ft_wall(t_jeux *game, int i, int dbt_pxl, int fin_pxl, int hautr_mur, int txt_i, int txt_x)
{
	int y;
	int txt_y;
	int coll;

	y = dbt_pxl;
	while (y < fin_pxl) 
	{
		txt_y = ((y - dbt_pxl) * game->cub.texture[txt_i].height) / hautr_mur;

		if (txt_x >= 0 && txt_x < game->cub.texture[txt_i].width &&
			txt_y >= 0 && txt_y < game->cub.texture[txt_i].height) 
		{
			coll = *(int *)(game->cub.texture[txt_i].addr 
						+ (txt_y * game->cub.texture[txt_i].size_line + txt_x * (game->cub.texture[txt_i].bpp / 8)));
			if (y >= 0 && y < HEIGHT) 
			{
				*(int *)(game->data + (y * game->size_line + i * (game->bpp / 8))) = coll;
			}
		}
		y++;
	}
}

// Render floor
void ft_floor(t_jeux *game, int i, int fin_pxl)
{
	int y;
	int txt_x;
	int txt_y;
	int coll;

	y = fin_pxl;
	while(y < HEIGHT)
	{
		txt_x = (i * game->cub.txt_plat.width) / WIDTH;
		txt_y = ((y - HEIGHT / 2) * game->cub.txt_plat.height) / (HEIGHT / 2);

		if (txt_x >= 0 && txt_x < game->cub.txt_plat.width &&
			txt_y >= 0 && txt_y < game->cub.txt_plat.height)
		{
			coll = *(int *)(game->cub.txt_plat.addr 
						+ (txt_y * game->cub.txt_plat.size_line + txt_x * (game->cub.txt_plat.bpp / 8)));
			*(int *)(game->data + (y * game->size_line + i * (game->bpp / 8))) = coll;
		}
		y++;
	}
}

void cast_ray(t_jeux *game, float start, int i)
{
	float cos_angle, sin_angle, fb_x, fb_y, ray_x, ray_y;
	float distance, corr_dst;
	int march_x, march_y;
	float ch_x, ch_y;
	int is_vertical_hit;
	int txt_i, txt_x;
	int cast_x;
	int cast_y;
	int hautr_mur;
	int dbt_pxl;
	int fin_pxl;

	txt_i = -1;
	txt_x = 0;
	ft_init_r(game, start, &cos_angle, &sin_angle, &fb_x, &fb_y, &ray_x, &ray_y);
	cast_x = (int)ray_x;
	cast_y = (int)ray_y;
	distance = ft_calc_distan(game, &ray_x, &ray_y, cos_angle, sin_angle);
	corr_dst = fabs(distance * cos(start - game->cub.player.angle));
	hautr_mur = (HEIGHT * 50) / corr_dst;
	dbt_pxl = (HEIGHT / 2) - (hautr_mur / 2);
	fin_pxl = (HEIGHT / 2) + (hautr_mur / 2);
	ft_algo(cos_angle, sin_angle, &march_x, &march_y, &ch_x, &ch_y, 
			  &cast_x, &cast_y, game->cub.player.player_x, game->cub.player.player_y);
	perform_dda(&cast_x, &cast_y, &ch_x, &ch_y, fb_x, fb_y, 
			   march_x, march_y, &is_vertical_hit, game->cub.cub_map);
	ft_soll(game, i, dbt_pxl);
	ft_coord(is_vertical_hit, march_x, march_y, ray_x, ray_y, &txt_i, &txt_x, game);
	ft_wall(game, i, dbt_pxl, fin_pxl, hautr_mur, txt_i, txt_x);
	ft_floor(game, i, fin_pxl);
}

int	my_raycasting_function(t_jeux *game)
{
	float next = (PI / 3) / WIDTH;
	float start = game->cub.player.angle  - (PI / 6);
	int i = 0;
	static int	index = 0;
	static int	frame_counter = 0;
	int			width;
	int			height;

	if (index >= FRAMES)
		index = 0;
	width = game->cub.player.width_player[index];  
	height = game->cub.player.height_player[index];
	while(i < WIDTH)
	{
		cast_ray(game, start, i);
		start += next;
		i++;
	}
	if (game->keys.up == 1)
		put_pl_hands(game, game->cub.player.addr_player[index], width, height);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	if (++frame_counter >= 2 && game->keys.up == 1)
	{
		frame_counter = 0;
		index+=4;
	}
	return (0);
}
