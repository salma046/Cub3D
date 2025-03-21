/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibahouch <ibahouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:20:24 by bimane            #+#    #+#             */
/*   Updated: 2025/03/21 07:33:04 by ibahouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	ft_algo(t_ray *ray, t_rendering *render, t_jeux *game)
{
	(void)render;
	if (ray->cos_angle < 0)
	{
		ray->march_x = -1;
		ray->ch_x = (game->cub.player.player_x - ray->cast_x) * fabs(1
				/ ray->cos_angle);
	}
	else
	{
		ray->march_x = 1;
		ray->ch_x = (ray->cast_x + 1 - game->cub.player.player_x) * fabs(1
				/ ray->cos_angle);
	}
	if (ray->sin_angle < 0)
	{
		ray->march_y = -1;
		ray->ch_y = (game->cub.player.player_y - ray->cast_y) * fabs(1
				/ ray->sin_angle);
	}
	else
	{
		ray->march_y = 1;
		ray->ch_y = (ray->cast_y + 1 - game->cub.player.player_y) * fabs(1
				/ ray->sin_angle);
	}
}

void	perform_dda(t_ray *ray, char **cub_map)
{
	while (1)
	{
		ray->map_x = (int)(ray->cast_x / 50);
		ray->map_y = (int)(ray->cast_y / 50);
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_x >= WIDTH
			|| ray->map_y >= HEIGHT)
			break ;
		if (cub_map[ray->map_y][ray->map_x] == '1'
			|| cub_map[ray->map_y][ray->map_x] == 'D')
			break ;
		if (ray->ch_x < ray->ch_y)
		{
			ray->ch_x += ray->fb_x;
			ray->cast_x += ray->march_x;
			ray->is_vertical_hit = 1;
		}
		else
		{
			ray->ch_y += ray->fb_y;
			ray->cast_y += ray->march_y;
			ray->is_vertical_hit = 0;
		}
		if (ray->ch_x > 10000 || ray->ch_y > 10000)
			break ;
	}
}

void	ft_soll(t_jeux *game, int i, int dbt_pxl)
{
	int	y;
	int	txt_x;
	int	txt_y;
	int	coll;

	y = 0;
	while (y < dbt_pxl)
	{
		txt_x = (i * game->cub.txt_ciel.width) / WIDTH;
		txt_y = (y * game->cub.txt_ciel.height) / (HEIGHT / 2);
		coll = *(int *)(game->cub.txt_ciel.addr + (txt_y
					* game->cub.txt_ciel.size_line + txt_x
					* (game->cub.txt_ciel.bpp / 8)));
		*(int *)(game->data + (y * game->size_line + i * (game->bpp
						/ 8))) = coll;
		y++;
	}
}

int	ft_norm_ray(t_ray *ray, t_jeux *game)
{
	ray->map_x = (int)(ray->ray_x / 50);
	ray->map_y = (int)(ray->ray_y / 50);
	if (ray->map_y > 0 && ray->map_x > 0 && ray->map_y < game->cub.map_width
		&& ray->map_x < game->cub.map_heigh
		&& game->cub.cub_map[ray->map_y][ray->map_x] == 'D')
		return (0);
	return (1);
}

void	ft_coord2(t_jeux *game, int *txt_i, int *txt_x)
{
	if (*txt_x < 0)
		*txt_x = 0;
	if (*txt_x >= game->cub.texture[*txt_i].width)
		*txt_x = game->cub.texture[*txt_i].width - 1;
}
