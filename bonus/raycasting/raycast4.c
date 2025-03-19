/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibahouch <ibahouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:20:24 by bimane            #+#    #+#             */
/*   Updated: 2025/03/18 09:02:09 by ibahouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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
	int	txt_x;
	int	txt_y;
	int	coll;

	y = fin_pxl;
	while (y < HEIGHT)
	{
		txt_x = (i * game->cub.txt_plat.width) / WIDTH;
		txt_y = ((y - HEIGHT / 2) * game->cub.txt_plat.height) / (HEIGHT / 2);
		if (txt_x >= 0 && txt_x < game->cub.txt_plat.width && txt_y >= 0
			&& txt_y < game->cub.txt_plat.height)
		{
			coll = *(int *)(game->cub.txt_plat.addr + (txt_y
						* game->cub.txt_plat.size_line + txt_x
						* (game->cub.txt_plat.bpp / 8)));
			*(int *)(game->data + (y * game->size_line + i * (game->bpp
							/ 8))) = coll;
		}
		y++;
	}
}

int	switch_door(t_jeux *jeux, int j, int i)
{
	jeux->cub.cub_map[j][i] = '0';
	return (2);
}
