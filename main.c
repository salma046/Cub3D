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
	while (game->cub_map[i])
	{
		free(game->cub_map[i++]);
	}
	free(game->cub_map);
    printf("Error: %s\n", error_str);
    exit(0);
}

int check_textures(t_cub3d game)
{
	(void)game;
	// first check if there is only one xpm file
	// second no second I think that's all for now
	;
	return (1);
}

// int check_map(char *map)
// {
//     ;
//     return (1);
// }

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
    t_cub3d game;

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
	if (check_textures(game) == 0)
		return_error("wrong textures!");
	return_free_error("EVERY THING IS GoooooD\n", &game);
	return (54);
    // if (check_map(av[1]) == 0)
    //     return_error("map not valid!");

}

/////// IT IS A MUST TO ASSIGN ALL THE CUB3D ELEMENT TO NULLLLLLLLLL
////// THEN START READING THE MAPPPP 
/////  TRUST ME DO THAT FIRST..
