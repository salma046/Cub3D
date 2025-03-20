/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:20:24 by bimane            #+#    #+#             */
/*   Updated: 2025/03/19 14:22:05 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_wall(t_rendering *render, t_jeux *game, int i)
{
	int	y;
	int	txt_y;
	int	coll;

	y = render->dbt_pxl;
	while (y < render->fin_pxl)
	{
		txt_y = ((y - render->dbt_pxl)
				* game->cub.texture[render->txt_i].height) / render->hautr_mur;
		if (render->txt_x >= 0
			&& render->txt_x < game->cub.texture[render->txt_i].width
			&& txt_y >= 0 && txt_y < game->cub.texture[render->txt_i].height)
		{
			coll = *(int *)(game->cub.texture[render->txt_i].addr + (txt_y
						* game->cub.texture[render->txt_i].size_line
						+ render->txt_x * (game->cub.texture[render->txt_i].bpp
							/ 8)));
			if (y >= 0 && y < HEIGHT)
			{
				*(int *)(game->data + (y * game->size_line + i * (game->bpp
								/ 8))) = coll;
			}
		}
		y++;
	}
}

void	ft_floor(t_jeux *game, int i, int fin_pxl)
{
	int	y;

	y = fin_pxl;
	while (y < HEIGHT)
	{
		ft_put_pixel(i, y, game->cub.floor_co, game);
		y++;
	}
}
