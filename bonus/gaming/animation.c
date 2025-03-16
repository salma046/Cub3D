#include "../../cub3d.h"

void	ft_clean_pl_mlx(t_jeux *jeux)
{
	int	i;

	i = 0;
	mlx_destroy_window(jeux->mlx, jeux->win);
	mlx_destroy_image(jeux->mlx, jeux->cub.txt_ciel.img);
	mlx_destroy_image(jeux->mlx, jeux->cub.txt_plat.img);
	while (i < 4)
	{
		mlx_destroy_image(jeux->mlx, jeux->cub.texture[i].img);
		i++;
	}
	mlx_destroy_display(jeux->mlx);
	free(jeux->mlx);
}

void	init_imgs(t_jeux *jeux, t_cub3d *game, const char *s[FRAMES])
{
	int	i;

	i = 0;
	while (i < FRAMES)
	{
		game->player.player[i] = mlx_xpm_file_to_image(jeux->mlx, (char *)s[i],
				&game->player.width_player[i], &game->player.height_player[i]);
		if (!game->player.player[i])
		{
			ft_clean_pl_mlx(jeux);
			return_free_error("\nPlayer texture not found", game);
		}
		game->player.addr_player[i] = (int *)mlx_get_data_addr(
				game->player.player[i], &game->player.bpp_player[i],
				&game->player.size_line_player[i],
				&game->player.endian_player[i]);
		i++;
	}
}

void	parse_player_textures(t_cub3d *game, t_jeux *jeux)
{
	const char	*tex[FRAMES];

	fill_player_textures_1(tex);
	fill_player_textures_2(tex);
	fill_player_textures_3(tex);
	fill_player_textures_4(tex);
	init_imgs(jeux, game, tex);
}

void	ft_init_player(t_cub3d *game, t_jeux *jeux)
{
	game->player.player = malloc(FRAMES * sizeof(void *));
	game->player.addr_player = malloc(FRAMES * sizeof(int *));
	game->player.width_player = malloc(FRAMES * sizeof(int));
	game->player.height_player = malloc(FRAMES * sizeof(int));
	game->player.bpp_player = malloc(FRAMES * sizeof(int));
	game->player.size_line_player = malloc(FRAMES * sizeof(int));
	game->player.endian_player = malloc(FRAMES * sizeof(int));
	if (!game->player.player || !game->player.addr_player
		|| !game->player.width_player || !game->player.height_player
		|| !game->player.bpp_player || !game->player.size_line_player
		|| !game->player.endian_player)
		return_free_error("\nFailed allocation!", game);
	parse_player_textures(game, jeux);
}
