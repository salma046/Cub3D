#include "cub3d.h"


int main(int ac, char *av[])
{
	t_cub3d	*game;
	/*Cest mieux que votre struct game etre dans le struct jeux */
	t_jeux	jeux;

	check_file(ac, av[1]);
	game = &jeux.cube;
	game->cub = read_file(av[1]);
	if (!game->cub)
		return_error("Invalid map!");
	parsing(game);
	return_free_error("EVERY THING IS GoooooD\n", game);

	/* Debut de raycasting
	 * mlx hook
	*/
	// mlx_loop_hook(jeux.mlx,ft_start,&jeux);

	return (54);

}
