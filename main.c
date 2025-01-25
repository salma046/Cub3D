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
				count++;
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


// 	char **read_cubmap;

// 	read_cubmap = map;
// 	int i = 0;
// 	while(read_cubmap[i])
// 	{
// 		printf("%s", read_cubmap[i]);
// 		i++;
// 	}

int check_map(t_cub3d *game)
{
	// first check for only one player
	// seconde check the map is surroudded by walls only if there is a spaces on the first and last edges
	check_for_player(game);
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
