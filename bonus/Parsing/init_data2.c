/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:32:15 by salaoui           #+#    #+#             */
/*   Updated: 2025/03/20 11:53:47 by salaoui          ###   ########.fr       */
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

int	check_edges(char **map, int i, int j, int height)
{
	while (map[i][j])
	{
		if (i == 0 || i == height - 1)
		{
			while (ft_isspace(map[i][j], 1))
				j++;
			if (map[i][j] != '\0' && map[i][j] != '\n' && map[i][j] != '1')
				return (0);
		}
		j++;
	}
	if (map[i][j - 1] == '\n' && map[i][j - 2] != '1')
		return (0);
	return (1);
}

int	check_one_in_edges(t_cub3d *game)
{
	char	**read_cubmap;
	int		i;
	int		j;

	i = 0;
	read_cubmap = game->cub_map;
	while (read_cubmap[i])
	{
		j = 0;
		while (read_cubmap[i] && !is_empty(read_cubmap[i]))
		{
			i++;
			if (!read_cubmap[i])
				return (1);
		}
		while (read_cubmap[i][j + 1] && ft_isspace(read_cubmap[i][j], 0))
			j++;
		if (read_cubmap[i][j] && read_cubmap[i][j] != '1')
			return (0);
		if (!check_edges(read_cubmap, i, j, game->map_heigh))
			return (0);
		i++;
	}
	return (1);
}
