#include "cub3d.h"

void ft_put_pixel(int x, int y, int color, t_jeux *game)
{
    if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
    
    int index = y * game->size_line + x * game->bpp / 8;
    game->data[index] = color & 0xFF;
    game->data[index + 1] = (color >> 8) & 0xFF;
    game->data[index + 2] = (color >> 16) & 0xFF;
	// exit(32);
}

void put_player(int x, int y, int color, t_jeux *game)
{
	ft_put_pixel(x, y, color, game);
}



void ft_rota_sour(int dir, t_jeux *game,float rot)
{


	if(dir == RIGHT)
		game->cub.player.angle -= rot;
	else if(dir == LEFT)
		game->cub.player.angle += rot;
	
	if(game->cub.player.angle < 0)
		game->cub.player.angle += 2 * PI;
	else if (game->cub.player.angle > 2 * PI)
		game->cub.player.angle -= 2 * PI;	
}


int ft_mouse(int x, int y, t_jeux *game)
{
	static int prch= -1;
	float rot_vt;

	rot_vt = 0.001;
	(void)y;

	if(prch == -1)
		prch = x;
	
	if(prch < x )
		ft_rota_sour(RIGHT, game,rot_vt * (x - prch));
	else if(prch > x)
		ft_rota_sour(LEFT,game, rot_vt * (prch - x));
	prch = x;
	return(0);

}

int main(int ac, char *av[])
{
	/*Cest mieux que votre struct game etre dans le struct jeux */
	t_cub3d	*game;
	t_jeux	jeux;

	check_file(ac, av[1]);
	game = &jeux.cub;
	game->cub = read_file(av[1]);
	if (!game->cub)
		return_error("Invalid map!");
	parsing(game, &jeux);
	jeux.mlx = mlx_init();
	ft_init_text(game, jeux.mlx);
	jeux.win = mlx_new_window(jeux.mlx, WIDTH, HEIGHT, "Cub3d");
	jeux.img = mlx_new_image(jeux.mlx, WIDTH, HEIGHT);

    jeux.data = mlx_get_data_addr(jeux.img, &jeux.bpp, &jeux.size_line, &jeux.endian);
    mlx_put_image_to_window(jeux.mlx, jeux.win, jeux.img, 0, 0);
	
	mlx_hook(jeux.win, 6, 1L << 6, ft_mouse, &jeux);

	mlx_hook(jeux.win, 2, 1L<<0, handle_key_press, &jeux);
	
	mlx_hook(jeux.win, 3, 1L<<1, handle_key_release, &jeux);
	mlx_loop_hook(jeux.mlx, gaming_ft, &jeux);
	// mlx_key_hook(jeux.win, move_player, &jeux);
	mlx_loop(jeux.mlx);
	return_free_error("EVERY THING IS GoooooD\n", game);

	/* Debut de raycasting
	 * mlx hook
	*/
	// mlx_loop_hook(jeux.mlx,ft_start,&jeux);

	return (54);

}
