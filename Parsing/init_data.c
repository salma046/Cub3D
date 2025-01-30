#include "../cub3d.h"

void	replace_empty_chars(t_cub3d *game)
{
	int		i;
	int		curr_len;
	char	**read_copy;
	char	*fill_line;

	read_copy = game->cub_copymap;
	i = 0;
	while (read_copy[i])
	{
		curr_len = ft_strlen(read_copy[i]);
		if (curr_len < game->map_width)
		{
			fill_line = (char *)malloc((game->map_width - curr_len + 1) * sizeof(char));
			if (!fill_line)
				return;
			ft_memset(fill_line, '\0', game->map_width - curr_len);
			fill_line[game->map_width - curr_len] = '\0';
			char *n_str = ft_my_strjoin(read_copy[i], fill_line);
			free(read_copy[i]);
			game->cub_copymap[i] = n_str;
			free(fill_line);
		}
		else
		{
			if (read_copy[i][curr_len - 1] == '\n')
			{
				char *n_str = ft_substr(read_copy[i], 0, curr_len - 1);
				free(read_copy[i]);
				game->cub_copymap[i] = n_str;
			}
		}
		i++;
	}
}

int	check_no_spaces(char **map, int x, int y)
{
	if (map[x - 1][y] == ' ' || map[x - 1][y] == '\0')
		return (0);
	if (map[x + 1][y] == ' ' || map[x + 1][y] == '\0')
		return (0);
	if (map[x][y - 1] == ' ' || map[x][y - 1] == '\0')
		return (0);
	if (map[x][y + 1] == ' ' || map[x][y + 1] == '\0')
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
			if (parsing[i][j] == game->player.dir_player || parsing[i][j] == '0')
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

void	valid_chars(t_cub3d *game)
{
	char	**read_cubmap;
	int		i;
	int		j;

	i = 0;
	read_cubmap = game->cub_map;
	while (read_cubmap[i])
	{
		j = 0;
		while (read_cubmap[i][j])
		{
			if (read_cubmap[i][j] != game->player.dir_player &&
				read_cubmap[i][j] != '1' && read_cubmap[i][j] != '\n' &&
					read_cubmap[i][j] != '0' && read_cubmap[i][j] != ' ')
				return_free_error("Invalid charachers!", game);
			j++;
		}
		i++;
	}
}

int check_map(t_cub3d *game)
{
	check_for_player(game);
	valid_chars(game);
	// if (check_one_in_edges(game) == 0)
	// 	return_free_error("INvalid Map!", game);
	//// check only valid caracters found
	make_a_copy(game);
	replace_empty_chars(game);
	if (!is_this_map_valid(game))
		return (0);
	return (1);
}

void    init_data(t_cub3d *game)
{
	int i;
	i = 0;
	game->no_texture = NULL;
	game->so_texture = NULL;
	game->we_texture = NULL;
	game->ea_texture = NULL;
	while (i < 3)
	{
		game->f_color[i] = -1;
		game->c_color[i] = -1;
		i++;
	}
	game->cub_map = NULL;
	game->cub_copymap = NULL;
	game->map_heigh = 0;
	game->map_width = 0;
}
