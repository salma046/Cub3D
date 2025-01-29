#include "cub3d.h"

int return_error(char *error_str)
{
	printf("Error: %s\n", error_str);
	exit(0);
}

int return_free_error(char *error_str, t_cub3d *game)
{
	char **temp;
	int i;

	i = 0;
	temp = game->cub;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
	if (game->no_texture)
		free(game->no_texture);
	if (game->so_texture)
		free(game->so_texture);
	if (game->we_texture)
		free(game->we_texture);
	if (game->ea_texture)
		free(game->ea_texture);
	i = 0;
	while (game->cub_map && game->cub_map[i])
	{
		free(game->cub_map[i++]);
	}
	free(game->cub_map);
	i = 0;
	while (game->cub_copymap && game->cub_copymap[i])
	{
		free(game->cub_copymap[i++]);
	}
	free(game->cub_copymap);
	printf("Error: %s\n", error_str);
	exit(0);
}

int check_textures(t_cub3d *game)
{
	(void)game;
	// first check if there is only one xpm file
	// second no second I think that's all for now
	;
	return (1);
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
			ft_memset(fill_line, 'X', game->map_width - curr_len);
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
		printf("***%s\n", read_copy[i]);
		i++;
	}
}

int	check_zeros_enclosed(char **map, int map_height)
{
	int	i;
	int	j;

	// Loop through each row (excluding the edges)
	for (i = 1; i < map_height - 1; i++) 
	{
		j = 1; // Start at the second column to avoid edges
		while (map[i][j + 1] != '\0') // Check within bounds of the current row
		{
			if (map[i][j] == '0') // Found a walkable tile
			{
				// Ensure the adjacent tiles are valid
				if (i - 1 < 0 || map[i - 1][j] != '1') // Top
					return (0);
				if (i + 1 >= map_height || map[i + 1][j] != '1') // Bottom
					return (0);
				if (j - 1 < 0 || map[i][j - 1] != '1') // Left
					return (0);
				if (j + 1 >= (int)ft_strlen(map[i]) || map[i][j + 1] != '1') // Right
					return (0);
			}
			j++;
		}
	}
	return (1);
}


int check_map(t_cub3d *game)
{
	// first check for only one player
	// seconde check the map is surroudded by walls only if there is a spaces on the first and last edges
	check_for_player(game);
	if (check_one_in_edges(game) == 0)
		return_free_error("NO ones on edges!", game);
	//// check only valid caracters found 
	make_a_copy(game);
	replace_empty_chars(game);///// replace the empty with 'X' char and go directly to check edges around the 0's and space's and player as well
	if (!check_zeros_enclosed((game->cub_copymap), game->map_heigh))
		return_free_error("zeros are not correctly enclosed", game);
	// int i = 0;
	// char **readdd_copy;

	// readdd_copy = game->cub_copymap;
	// if (!game->cub_copymap[i])
	// 	printf("it's nullllll\n");
	// while (readdd_copy[i])
	// {
	// 	printf("*%s", readdd_copy[i]);
	// 	i++;
	// }
	//// in this step check if the spaces are between 1ones on the map 
	////last step
	// if (can_exit_map_from_pos(game, 1, 1))
	// 	return_free_error("can't exit map from pos", game);
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

int main(int ac, char *av[])
{
	t_cub3d	game;

	if (ac != 2)
		return_error("Arguments not valid!");
	if (check_file_valid(av[1]) == 0)
		return_error("Cannot open file!");
	game.cub = read_file(av[1]);
	if (!game.cub)
		return_error("Invalid map!");
	init_data(&game);
	if (!split_my_elements(&game))/// this function split the textures from the map and put each on the appropriate place
		return_free_error("Invalid map!", &game);
	if (check_textures(&game) == 0)
		return_free_error("wrong textures!", &game);
	if (check_map(&game) == 0)
		return_free_error("map not valid!", &game);
	return_free_error("EVERY THING IS GoooooD\n", &game);
	return (54);

}
