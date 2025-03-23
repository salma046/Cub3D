/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:20:24 by bimane            #+#    #+#             */
/*   Updated: 2025/03/23 16:44:47 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	no_edge(char **map, int i, int j)
{
	if (map[i][j] == 'D')
	{
		if (i == 0 || j == 0 || map[i + 1] == NULL || map[i][j + 1] == '\0')
			return (0);
		if (map[i - 1][j] == ' ' || map[i + 1][j] == ' '
			|| map[i][j - 1] == ' ' || map[i][j + 1] == ' ' )
			return (0);
		if (map[i][j - 1] == '-' || map[i][j + 1] == '-'
				|| map[i - 1][j] == '-' || map[i + 1][j] == '-')
			return (0);
	}
	return (1);
}

void	ft_rota_sour(int dir, t_jeux *game, float rot)
{
	if (dir == RIGHT)
		game->cub.player.angle -= rot;
	else if (dir == LEFT)
		game->cub.player.angle += rot;
	if (game->cub.player.angle < 0)
		game->cub.player.angle += 2 * PI;
	else if (game->cub.player.angle > 2 * PI)
		game->cub.player.angle -= 2 * PI;
}

int	ft_mouse(int x, int y, t_jeux *game)
{
	static int	prch = -1;
	float		rot_vt;

	rot_vt = 0.001;
	(void)y;
	if (prch == -1)
		prch = x;
	if (prch < x)
		ft_rota_sour(LEFT, game, rot_vt * (x - prch));
	else if (prch > x)
		ft_rota_sour(RIGHT, game, rot_vt * (prch - x));
	prch = x;
	return (0);
}
