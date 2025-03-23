/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:27:03 by salaoui           #+#    #+#             */
/*   Updated: 2025/03/23 16:43:13 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_short_lines(t_cub3d *game, int i)
{
	int		curr_len;
	char	*fill_line;
	char	*n_str;
	char	**read_copy;

	read_copy = game->cub_copymap;
	curr_len = ft_strlen(read_copy[i]);
	if (curr_len < game->map_width)
	{
		fill_line = (char *)malloc((game->map_width - curr_len + 1)
				* sizeof(char));
		if (!fill_line)
			return ;
		ft_memset(fill_line, '-', game->map_width - curr_len);
		fill_line[game->map_width - curr_len] = '\0';
		n_str = ft_my_strjoin(read_copy[i], fill_line);
		free(read_copy[i]);
		game->cub_copymap[i] = n_str;
		free(fill_line);
	}
}

void	remove_newline_end(t_cub3d *game, int i)
{
	int		curr_len;
	char	*n_str;
	char	**read_copy;

	read_copy = game->cub_copymap;
	curr_len = ft_strlen(read_copy[i]);
	if (curr_len > 0 && read_copy[i][curr_len - 1] == '\n')
	{
		n_str = ft_substr(read_copy[i], 0, curr_len - 1);
		free(read_copy[i]);
		game->cub_copymap[i] = n_str;
	}
}

void	replace_empty_chars(t_cub3d *game)
{
	int		i;

	i = 0;
	while (game->cub_copymap[i])
	{
		fill_short_lines(game, i);
		remove_newline_end(game, i);
		i++;
	}
}

int	check_no_spaces(char **map, int x, int y)
{
	if (x == 0 || y == 0 || map[x + 1] == NULL || map[x][y + 1] == '\0')
		return (0);
	if (map[x - 1][y] == ' ' || map[x - 1][y] == '-')
		return (0);
	if (map[x + 1][y] == ' ' || map[x + 1][y] == '-')
		return (0);
	if (map[x][y - 1] == ' ' || map[x][y - 1] == '-')
		return (0);
	if (map[x][y + 1] == ' ' || map[x][y + 1] == '-')
		return (0);
	return (1);
}

int	is_this_map_valid(t_cub3d *game)
{
	int		i;
	int		j;
	char	**parsing;

	i = 0;
	parsing = game->cub_copymap;
	while (parsing[i])
	{
		j = 0;
		while (parsing[i][j])
		{
			if (parsing[i][j] == game->player.dir_player
				|| parsing[i][j] == '0')
			{
				if (!check_no_spaces(parsing, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
