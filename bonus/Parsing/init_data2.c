/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:32:15 by salaoui           #+#    #+#             */
/*   Updated: 2025/03/21 17:12:00 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (2);
}

int	check_for_player(t_cub3d *game)
{
	char	**read_cubmap;
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	read_cubmap = game->cub_map;
	while (read_cubmap[i])
	{
		j = 0;
		while (read_cubmap[i][j])
		{
			if (is_player(read_cubmap[i][j]) == 1)
			{
				game->player.player_y = i * 50;
				game->player.player_x = j * 50;
				game->player.dir_player = read_cubmap[i][j];
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

void	make_a_copy(t_cub3d *game)
{
	char	**to_read;
	int		i;
	int		largestline;

	i = 0;
	largestline = -1;
	to_read = game->cub_map;
	game->cub_copymap = (char **)malloc((game->map_heigh + 1) * sizeof(char *));
	while (to_read[i])
	{
		if ((int)ft_strlen(to_read[i]) > largestline)
			largestline = ft_strlen(to_read[i]);
		game->cub_copymap[i] = ft_strdup(to_read[i]);
		i++;
	}
	game->cub_copymap[i] = NULL;
	game->map_width = largestline;
}

int	check_doors(t_cub3d *game)
{
	char	**read_map;
	int		i;
	int		j;

	i = 0;
	read_map = game->cub_map;
	while (read_map[i])
	{
		j = 0;
		while (read_map[i][j] && ft_isspace(read_map[i][j], 1))
			j++;
		if (read_map[i][j] == 'D')
			return (0);
		while (read_map[i][j] && ft_isspace(read_map[i][j], 1))
			j++;
		if (!read_map[i][j] && read_map[i][j - 1] == 'D')
			return (0);
		i++;
	}
	return (1);
}
