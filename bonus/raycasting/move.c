/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:31:54 by salaoui           #+#    #+#             */
/*   Updated: 2025/03/19 11:31:55 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	rotate_player(t_jeux *jeux, float angle_rotation)
{
	if (jeux->keys.rrotate)
		jeux->cub.player.angle += angle_rotation;
	if (jeux->keys.lrotate)
		jeux->cub.player.angle -= angle_rotation;
}

void	move_forward_backward(t_jeux *jeux, t_movement *move)
{
	if (jeux->keys.up)
	{
		move->next_x += move->move_cos;
		move->next_y += move->move_sin;
	}
	if (jeux->keys.down)
	{
		move->next_x -= move->move_cos;
		move->next_y -= move->move_sin;
	}
}

void	move_sideways(t_jeux *jeux, t_movement *move)
{
	if (jeux->keys.right)
	{
		move->next_x -= move->move_sin;
		move->next_y += move->move_cos;
	}
	if (jeux->keys.left)
	{
		move->next_x += move->move_sin;
		move->next_y -= move->move_cos;
	}
}

void	move_player(t_jeux *jeux)
{
	float		angle_rotation;
	float		x_player;
	float		y_player;
	t_movement	move;

	angle_rotation = 0.03;
	x_player = jeux->cub.player.player_x;
	y_player = jeux->cub.player.player_y;
	move.next_x = x_player;
	move.next_y = y_player;
	move.move_cos = 3 * cos(jeux->cub.player.angle);
	move.move_sin = 3 * sin(jeux->cub.player.angle);
	rotate_player(jeux, angle_rotation);
	move_forward_backward(jeux, &move);
	move_sideways(jeux, &move);
	if (no_walls(move.next_x, y_player, jeux->cub.cub_map))
		jeux->cub.player.player_x = move.next_x;
	if (no_walls(x_player, move.next_y, jeux->cub.cub_map))
		jeux->cub.player.player_y = move.next_y;
}

int	ft_porte(t_jeux *jeux)
{
	int	map[2];
	int	dy;
	int	dx;
	int	check[2];

	map[0] = (int)(jeux->cub.player.player_x / 50);
	map[1] = (int)(jeux->cub.player.player_y / 50);
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			check[0] = map[0] + dx;
			check[1] = map[1] + dy;
			if (check[0] < 0 || check[1] < 0 || check[0] >= WIDTH / 50
				|| check[1] >= HEIGHT / 50)
				continue ;
			if (jeux->cub.cub_map[check[1]][check[0]] == 'D')
				return (switch_door(jeux, check[1], check[0]));
			dx++;
		}
		dy++;
	}
	return (0);
}
