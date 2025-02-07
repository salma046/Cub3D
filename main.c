#include "cub3d.h"

int	move_player(int key_press, t_jeux *game)
{
	if (key_press == 65307)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	return (1);
}


int main(int ac, char *av[])
{
	/*Cest mieux que votre struct game etre dans le struct jeux */
	t_cub3d	*game;
	t_jeux	jeux;

	check_file(ac, av[1]);
	game = &jeux.cube;
	game->cub = read_file(av[1]);
	if (!game->cub)
		return_error("Invalid map!");
	parsing(game);
	jeux.mlx = mlx_init();
	jeux.win = mlx_new_window(jeux.mlx, 1300, 700, "Cub3d");
	mlx_key_hook(jeux.win, move_player, &jeux);
	mlx_loop(jeux.mlx);
	return_free_error("EVERY THING IS GoooooD\n", game);

	/* Debut de raycasting
	 * mlx hook
	*/
	// mlx_loop_hook(jeux.mlx,ft_start,&jeux);

	return (54);

}
