/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_frames.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:34:18 by salaoui           #+#    #+#             */
/*   Updated: 2025/03/19 11:34:19 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	player_data(t_jeux *game, t_player_data *player, int texture_width,
		int texture_height)
{
	player->src_index = 0;
	player->i = 0;
	player->img_addr = (unsigned int *)game->data;
	player->x_scale = (float)(texture_width - 20) / WIDTH;
	player->y_scale = (float)(texture_height - 20) / HEIGHT;
}

void	scale(t_player_data *player, int texture_width)
{
	player->texture_x = (int)(player->j * player->x_scale);
	player->texture_y = (int)(player->i * player->y_scale);
	player->src_index = player->texture_x + player->texture_y * texture_width;
	if (player->j >= 0 && player->j < WIDTH && player->i >= 0
		&& player->i < HEIGHT)
	{
		if (player->texture_addr[player->src_index] != 0xff000000)
		{
			player->img_addr[player->j + player->i
				* WIDTH] = player->texture_addr[player->src_index];
		}
	}
}

void	put_pl_hands(t_jeux *game, int *pl, int texture_width,
		int texture_height)
{
	t_player_data	*player;

	player = malloc(sizeof(t_player_data));
	if (!player)
		return ;
	player->texture_addr = (unsigned int *)pl;
	player_data(game, player, texture_width, texture_height);
	while (player->i < HEIGHT)
	{
		player->j = 0;
		while (player->j < WIDTH)
		{
			scale(player, texture_width);
			player->j++;
		}
		player->i++;
	}
	free(player);
}
