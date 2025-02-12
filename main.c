#include "cub3d.h"

int	move_player(int key_press, t_jeux *game)
{
	float	angle_rotation;

	angle_rotation = 0.01;
	while (key_press == 65363)
	{
		printf("hello world\n");
		game->cube.player.dir_player += angle_rotation;
	}
	if (key_press == 65307)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	// if (key_press == 119)
	// 	i = up_handle(key_press, game);
	// if (key_press == 115)
	// 	i = down_handle(key_press, game);
	// if (key_press == 100)
	// 	i = right_handle(key_press, game);
	// if (key_press == 97)
	// 	i = left_handle(key_press, game);
	// if (i != 0)
	// 	put_images_in_window(game->mlx, game->mlx_win, game);
	return (1);
}


void put_pixel(int x, int y, int color, t_jeux *game)
{
    if(x >= 1300 || y >= 700 || x < 0 || y < 0)
        return;
    
    int index = y * game->size_line + x * game->bpp / 8;
    game->data[index] = color & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = (color >> 16) & 0xFF;
}



void put_player(int x, int y, int color, t_jeux *game)
{
	put_pixel(x, y, color, game);
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
	jeux.img = mlx_new_image(jeux.mlx, 1300, 700);
    jeux.data = mlx_get_data_addr(jeux.img, &jeux.bpp, &jeux.size_line, &jeux.endian);
    mlx_put_image_to_window(jeux.mlx, jeux.win, jeux.img, 0, 0);
	// put_player(game->player.player_x, game->player.player_y, 0x00FF00, &jeux);///here
	my_raycasting_function(&jeux);
	mlx_key_hook(jeux.win, move_player, &jeux);
	mlx_loop(jeux.mlx);
	return_free_error("EVERY THING IS GoooooD\n", game);

	/* Debut de raycasting
	 * mlx hook
	*/
	// mlx_loop_hook(jeux.mlx,ft_start,&jeux);

	return (54);

}
