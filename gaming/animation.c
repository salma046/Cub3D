#include "../cub3d.h"

void	init_imgs(t_jeux *jeux, t_cub3d *game, const char *s[FRAMES])
{
	int	i;

	i = 0;
	while (i < FRAMES)
	{
		game->player.player[i] = mlx_xpm_file_to_image(jeux->mlx, (char *)s[i],
				&game->player.width_player[i],
				&game->player.height_player[i]);
        if (!game->player.player[i])
	    {
		    return_free_error("\nPlayer texture not found", game);
	    }  
		game->player.addr_player[i] = (int *)mlx_get_data_addr(
				game->player.player[i], &game->player.bpp_player[i],
				&game->player.size_line_player[i],
				&game->player.endian_player[i]);
        // printf("hello world\n");
		i++;
	}
}

void parse_player_textures(t_cub3d *game, t_jeux *jeux)
{
    const char *tex[FRAMES] = {
        "texture/player_anim/take1.xpm", "texture/player_anim/take2.xpm",
		"texture/player_anim/take3.xpm", "texture/player_anim/take4.xpm",
		"texture/player_anim/take5.xpm", "texture/player_anim/take6.xpm",
		"texture/player_anim/take7.xpm", "texture/player_anim/take8.xpm",
		"texture/player_anim/take9.xpm", "texture/player_anim/take10.xpm",
		"texture/player_anim/take11.xpm", "texture/player_anim/take12.xpm",
		"texture/player_anim/take13.xpm", "texture/player_anim/take14.xpm",
		"texture/player_anim/take15.xpm", "texture/player_anim/take16.xpm",
		"texture/player_anim/take17.xpm", "texture/player_anim/take18.xpm",
		"texture/player_anim/take19.xpm", "texture/player_anim/take20.xpm",
		"texture/player_anim/take21.xpm", "texture/player_anim/take22.xpm",
		"texture/player_anim/take23.xpm", "texture/player_anim/take24.xpm",
		"texture/player_anim/take25.xpm", "texture/player_anim/take26.xpm",
		"texture/player_anim/take27.xpm", "texture/player_anim/take28.xpm",
		"texture/player_anim/take29.xpm", "texture/player_anim/take30.xpm",
		"texture/player_anim/take31.xpm", "texture/player_anim/take32.xpm",
		"texture/player_anim/take33.xpm", "texture/player_anim/take34.xpm",
		"texture/player_anim/take35.xpm", "texture/player_anim/take36.xpm",
		"texture/player_anim/take37.xpm", "texture/player_anim/take38.xpm",
		"texture/player_anim/take39.xpm", "texture/player_anim/take40.xpm",
		"texture/player_anim/take41.xpm", "texture/player_anim/take42.xpm",
		"texture/player_anim/take43.xpm", "texture/player_anim/take44.xpm",
		"texture/player_anim/take45.xpm", "texture/player_anim/take46.xpm",
		"texture/player_anim/take47.xpm", "texture/player_anim/take48.xpm",
		"texture/player_anim/take49.xpm", "texture/player_anim/take50.xpm",
		"texture/player_anim/take51.xpm", "texture/player_anim/take52.xpm",
		"texture/player_anim/take53.xpm", "texture/player_anim/take54.xpm",
		"texture/player_anim/take55.xpm", "texture/player_anim/take56.xpm",
		"texture/player_anim/take57.xpm", "texture/player_anim/take58.xpm",
		"texture/player_anim/take59.xpm", "texture/player_anim/take60.xpm",
		"texture/player_anim/take61.xpm", "texture/player_anim/take62.xpm",
		"texture/player_anim/take63.xpm", "texture/player_anim/take64.xpm",
		"texture/player_anim/take65.xpm", "texture/player_anim/take66.xpm",
		"texture/player_anim/take67.xpm", "texture/player_anim/take68.xpm",
		"texture/player_anim/take69.xpm"};
	init_imgs(jeux, game, tex);
}

void ft_init_player(t_cub3d *game, t_jeux *jeux)
{
	game->player.player = malloc(FRAMES * sizeof(void *));
	game->player.addr_player = malloc(FRAMES * sizeof(int *));
	game->player.width_player = malloc(FRAMES * sizeof(int));
	game->player.height_player = malloc(FRAMES * sizeof(int));
	game->player.bpp_player = malloc(FRAMES * sizeof(int));
	game->player.size_line_player = malloc(FRAMES * sizeof(int));
	game->player.endian_player = malloc(FRAMES * sizeof(int));
	parse_player_textures(game, jeux);
}

