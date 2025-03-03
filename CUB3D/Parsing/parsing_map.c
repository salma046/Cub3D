#include "../cub3d.h"

int is_all_textures_found(t_cub3d *game)
{
	int	i;

	i = 0;
	if (!game->no_texture || !game->so_texture)
		return (0);
	if (!game->we_texture || !game->ea_texture)
        return (0);
	while(i < 3)
	{
		if (game->f_color[i] == -1)
			return (0);
		i++;
	}
	i = 0;
	while(i < 3)
	{
		if (game->c_color[i] == -1)
			return (0);
		i++;
	}
	return (1);
}

int	count_map_height(char **cub, int start)
{
	int	count;

	count = 0;
	while (cub[start])
	{
		count++;
		start++;
	}
	return (count);
}

int	check_end_map(char *line)
{
	if (line[0] == '\n')
		return (0);
	return (1);
}

int	fill_cub_map(t_cub3d *game, int i)
{
	char	**read_cub;
	int		height;
	int		j;

	read_cub = game->cub;
	j = 0;
	if (is_all_textures_found(game) == 0)
		return (0);
	height = count_map_height(game->cub, i);
	game->cub_map = (char **)malloc((height + 1) * sizeof(char *));
	game->map_heigh = height;
	while(read_cub[i] && check_end_map(read_cub[i]))
		game->cub_map[j++] = ft_strdup(read_cub[i++]);
	game->cub_map[j] = NULL;
	while (read_cub[i] && !check_end_map(read_cub[i]))
		i++;
	if (read_cub[i])
		return_free_error("Invalid Map!", game);
	return (1);
}

void	parsing(t_cub3d *game, t_jeux *jeux)
{
	init_data(game, jeux);
	if (!split_my_elements(game))
		return_free_error("Invalid map!", game);
	if (check_textures(game) == 0)
		return_free_error("wrong textures!", game);
	if (check_map(game) == 0)
		return_free_error("map not valid!", game);
}