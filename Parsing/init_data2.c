#include "../cub3d.h"

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
