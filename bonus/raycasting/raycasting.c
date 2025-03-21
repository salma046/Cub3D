/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibahouch <ibahouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:20:24 by bimane            #+#    #+#             */
/*   Updated: 2025/03/20 14:35:17 by ibahouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	ft_coord(t_ray *ray, int *txt_i, int *txt_x, t_jeux *game)
{
	if (ray->is_vertical_hit == 2)
		*txt_i = 4;
	else if (ray->is_vertical_hit)
	{
		if (ray->march_x == 1)
			*txt_i = 0;
		else
			*txt_i = 1;
	}
	else
	{
		if (ray->march_y == 1)
			*txt_i = 2;
		else
			*txt_i = 3;
	}
	if (game->cub.cub_map[ray->map_y][ray->map_x] == 'D')
		*txt_i = 4;
	ray->impact_x = ray->ray_x;
	if (ray->is_vertical_hit == 1)
		ray->impact_x = ray->ray_y;
	ray->impact_x = fmod(ray->impact_x, 50);
	*txt_x = (int)((ray->impact_x / 50.0) * (game->cub.texture[*txt_i].width
				- 1));
	ft_coord2(game, txt_i, txt_x);
}

void	cast_ray(t_jeux *game, float start, int i)
{
	t_ray		ray;
	t_rendering	render;

	render.txt_i = -1;
	render.txt_x = 0;
	ft_init_r(game, start, &ray);
	ray.cast_x = (int)ray.ray_x;
	ray.cast_y = (int)ray.ray_y;
	ray.distance = ft_calc_distan(game, &ray);
	ray.corr_dst = fabs(ray.distance * cos(start - game->cub.player.angle));
	render.hautr_mur = (HEIGHT * 50) / ray.corr_dst;
	render.dbt_pxl = (HEIGHT / 2) - (render.hautr_mur / 2);
	render.fin_pxl = (HEIGHT / 2) + (render.hautr_mur / 2);
	ft_algo(&ray, &render, game);
	perform_dda(&ray, game->cub.cub_map);
	ft_soll(game, i, render.dbt_pxl);
	ft_coord(&ray, &render.txt_i, &render.txt_x, game);
	ft_wall(&render, game, i);
	ft_floor(game, i, render.fin_pxl);
}

int	my_raycasting_function(t_jeux *game)
{
	t_var		var;
	static int	index = 0, frame_counter = 0;

	var.next = (PI / 3) / WIDTH;
	var.start = game->cub.player.angle - (PI / 6);
	if (index >= FRAMES)
		index = 0;
	var.i = 0;
	var.h = game->cub.player.height_player[index];
	var.w = game->cub.player.width_player[index];
	while (var.i < WIDTH)
	{
		cast_ray(game, var.start, var.i);
		var.start += var.next;
		var.i++;
	}
	if (game->keys.up == 1)
		put_pl_hands(game, game->cub.player.addr_player[index], var.w, var.h);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	if (++frame_counter >= 2 && game->keys.up == 1)
	{
		frame_counter = 0;
		index += 4;
	}
	return (0);
}
