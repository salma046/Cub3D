/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:28:50 by salaoui           #+#    #+#             */
/*   Updated: 2025/03/19 11:28:51 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	draw_player(int player_x, int player_y, int diametre, t_jeux *jeux)
{
	int	x;
	int	y;

	x = diametre - player_x;
	while (x < diametre + player_x)
	{
		y = diametre - player_y;
		while (y < diametre + player_y)
		{
			if (((y - player_y) * (y - player_y) + (x - player_x) * (x
						- player_x)) <= diametre * diametre)
				ft_put_pixel(x, y, 0x51f5d9, jeux);
			y++;
		}
		x++;
	}
}

int	check_distance(t_wall wall, t_jeux *jeux, int color)
{
	int	pl_pos[2];
	int	new_wall[2];
	int	i;
	int	j;

	pl_pos[0] = jeux->cub.player.player_y / 50;
	pl_pos[1] = jeux->cub.player.player_x / 50;
	if (abs(pl_pos[0] - wall.wall_y) <= 7 && abs(pl_pos[1] - wall.wall_x) <= 13)
	{
		new_wall[0] = wall.mini_x + ((wall.wall_x - pl_pos[1]) * 20);
		new_wall[1] = wall.mini_y + ((wall.wall_y - pl_pos[0]) * 20);
		i = -1;
		while (++i < 20)
		{
			j = -1;
			while (++j < 20)
			{
				if (((new_wall[0] + j) <= (WIDTH / 5) + 5 && (new_wall[0]
							+ j) >= 15) && ((new_wall[1] + i) <= (HEIGHT / 5)
						+ 5 && (new_wall[1] + i >= 15)))
					ft_put_pixel(new_wall[0] + j, new_wall[1] + i, color, jeux);
			}
		}
	}
	return (0);
}

void	draw_walls(int p_x, int p_y, t_jeux *jeux)
{
	int		i;
	int		j;
	t_wall	wall;

	wall.mini_x = p_x;
	wall.mini_y = p_y;
	i = 0;
	while (jeux->cub.cub_map[i])
	{
		j = 0;
		while (jeux->cub.cub_map[i][j])
		{
			wall.wall_x = j;
			wall.wall_y = i;
			if (jeux->cub.cub_map[i][j] == '1'
				|| jeux->cub.cub_map[i][j] == 'D')
				check_distance(wall, jeux, 0x3291a8);
			if (jeux->cub.cub_map[i][j] == '0'
				|| jeux->cub.cub_map[i][j] == jeux->cub.player.dir_player)
				check_distance(wall, jeux, 0xd1b2b0);
			j++;
		}
		i++;
	}
}

void	mini_map(t_jeux *jeux)
{
	int	map_width;
	int	map_height;
	int	player_x;
	int	player_y;

	map_width = WIDTH / 5;
	map_height = HEIGHT / 5;
	player_x = map_width / 2;
	player_y = map_height / 2;
	draw_walls(player_x, player_y, jeux);
	draw_player(player_x, player_y, 5, jeux);
}
