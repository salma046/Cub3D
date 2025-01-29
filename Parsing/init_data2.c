#include "../cub3d.h"

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
			if (read_cubmap[i][j] == 'N' || read_cubmap[i][j] == 'S' ||
					read_cubmap[i][j] == 'W' || read_cubmap[i][j] == 'E')
			{
				game->player.player_x = i;
				game->player.player_y = j;
				game->player.dir_player = read_cubmap[i][j];
				count++;
			}
			j++;
		}
		i++;
	}
	if (count == 0)
		return_free_error("No player found!", game);
	else if (count != 1)
		return_free_error("Multiple players found!", game);
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
		while(read_cubmap[i] && !is_empty(read_cubmap[i]))
		{
			i++;
			if (!read_cubmap[i])
				return (1);
		}
		while (read_cubmap[i][j + 1] && ft_isspace(read_cubmap[i][j], 0))
			j++;
		if (read_cubmap[i][j] && read_cubmap[i][j] != '1')
			return (0);
		while (read_cubmap[i][j])
		{
			if (i == 0 || i == game->map_heigh - 1)
			{
				while (ft_isspace(read_cubmap[i][j], 1))
					j++;
				if (read_cubmap[i][j] != '\0' && read_cubmap[i][j] != '\n' && read_cubmap[i][j] != '1')
					return (0);
			}
			j++;
		}
		if (read_cubmap[i][j - 1] == '\n' && read_cubmap[i][j - 2] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	make_a_copy(t_cub3d *game)
{
	char **to_read;
	int i;
	int	largestline;

	i = 0;
	largestline = -1;
	to_read = game->cub_map;
	game->cub_copymap = (char **)malloc((game->map_heigh + 1) * sizeof(char *));
	while (to_read[i])
	{
		if ((int )ft_strlen(to_read[i]) > largestline)
			largestline = ft_strlen(to_read[i]);
		game->cub_copymap[i] = ft_strdup(to_read[i]);
		i++;
	}
	game->cub_copymap[i] = NULL;
	game->map_width = largestline;
}
