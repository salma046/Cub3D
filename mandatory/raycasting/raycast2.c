/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:20:24 by bimane            #+#    #+#             */
/*   Updated: 2025/03/22 12:59:01 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	no_walls(float ray_x, float ray_y, char **map)
{
	float	margin;
	int		x;
	int		y;

	margin = 10.0;
	x = ray_x / 50;
	y = ray_y / 50;
	if (map[y][x] == '1')
		return (0);
	if (map[(int)((ray_y - margin) / 50)][x] == '1')
		return (0);
	if (map[(int)((ray_y + margin) / 50)][x] == '1')
		return (0);
	if (map[y][(int)((ray_x - margin) / 50)] == '1')
		return (0);
	if (map[y][(int)((ray_x + margin) / 50)] == '1')
		return (0);
	return (1);
}

void	ft_init_text1(t_jeux *jeux, t_cub3d *game, void *mlx)
{
	char	*text[4];
	int		i;

	text[0] = game->ea_texture;
	text[1] = game->so_texture;
	text[2] = game->no_texture;
	text[3] = game->we_texture;
	i = 0;
	if (!mlx)
		return_error("\nmlx non initialisÃ© !");
	while (i < 4)
	{
		game->texture[i].img = mlx_xpm_file_to_image(mlx, text[i],
				&game->texture[i].width, &game->texture[i].height);
		if (!game->texture[i].img)
		{
			return_free_error("\nIvalid Texture image", game);
			mlx_destroy_display(jeux->mlx);
		}
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,
				&game->texture[i].bpp, &game->texture[i].size_line,
				&game->texture[i].endian);
		i++;
	}
}

void	ft_init_text2(t_jeux *jeux, t_cub3d *game, void *mlx)
{
	char	*cl;
	char	*pl;

	(void)jeux;
	cl = "texture/cl.xpm";
	pl = "texture/color_floor.xpm";
	game->txt_plat.img = mlx_xpm_file_to_image(mlx, pl, &game->txt_plat.width,
			&game->txt_plat.height);
	game->txt_plat.addr = mlx_get_data_addr(game->txt_plat.img,
			&game->txt_plat.bpp, &game->txt_plat.size_line,
			&game->txt_plat.endian);
	game->txt_ciel.img = mlx_xpm_file_to_image(mlx, cl, &game->txt_ciel.width,
			&game->txt_ciel.height);
	if (!game->txt_plat.img || !game->txt_ciel.img)
		return_free_error("\nIvalid Texture image", game);
	game->txt_ciel.addr = mlx_get_data_addr(game->txt_ciel.img,
			&game->txt_ciel.bpp, &game->txt_ciel.size_line,
			&game->txt_ciel.endian);
}

void	ft_init_r(t_jeux *game, float start, t_ray *ray)
{
	ray->cos_angle = cos(start);
	ray->sin_angle = sin(start);
	ray->fb_x = fabs(1 / ray->cos_angle);
	ray->fb_y = fabs(1 / ray->sin_angle);
	ray->ray_x = game->cub.player.player_x;
	ray->ray_y = game->cub.player.player_y;
}

float	ft_calc_distan(t_jeux *game, t_ray *ray)
{
	float	distance;

	distance = 0;
	while (1)
	{
		ray->map_x = (int)(ray->ray_x / 50);
		ray->map_y = (int)(ray->ray_y / 50);
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_x >= WIDTH
			|| ray->map_y >= HEIGHT)
			break ;
		if (game->cub.cub_map[ray->map_y][ray->map_x] == '1'
			|| game->cub.cub_map[ray->map_y][ray->map_x] == 'D')
			break ;
		ray->ray_x += ray->cos_angle;
		ray->ray_y += ray->sin_angle;
		distance++;
	}
	return (distance);
}
