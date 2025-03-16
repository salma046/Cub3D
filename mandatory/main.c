#include "../cub3d.h"

int	handle_close_button(t_jeux *jeux)
{
	ft_clean_mlx(jeux);
	mlx_destroy_display(jeux->mlx);
	free(jeux->mlx);
	return_free_error("", &jeux->cub);
	return (0);
}

void	ft_put_pixel(int x, int y, int color, t_jeux *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	put_player(int x, int y, int color, t_jeux *game)
{
	ft_put_pixel(x, y, color, game);
}

int	main(int ac, char *av[])
{
	t_cub3d	*game;
	t_jeux	jeux;

	check_file(ac, av[1]);
	game = &jeux.cub;
	game->cub = read_file(av[1]);
	if (!game->cub)
		return_error("\nInvalid map!");
	parsing(game, &jeux);
	jeux.mlx = mlx_init();
	ft_init_text(&jeux, game, jeux.mlx);
	jeux.win = mlx_new_window(jeux.mlx, WIDTH, HEIGHT, "Cub3d");
	jeux.img = mlx_new_image(jeux.mlx, WIDTH, HEIGHT);
	jeux.data = mlx_get_data_addr(jeux.img, &jeux.bpp, &jeux.size_line,
			&jeux.endian);
	mlx_put_image_to_window(jeux.mlx, jeux.win, jeux.img, 0, 0);
	mlx_hook(jeux.win, 2, 1L << 0, handle_key_press, &jeux);
	mlx_hook(jeux.win, 3, 1L << 1, handle_key_release, &jeux);
	mlx_hook(jeux.win, 17, 0, handle_close_button, &jeux);
	mlx_loop_hook(jeux.mlx, gaming_ft, &jeux);
	mlx_loop(jeux.mlx);
}
