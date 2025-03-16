#include "../cub3d.h"

void	valid_chars(t_cub3d *game)
{
	char	**read_cubmap;
	int		i;
	int		j;

	i = 0;
	read_cubmap = game->cub_map;
	while (read_cubmap[i])
	{
		j = 0;
		while (read_cubmap[i][j])
		{
			if (read_cubmap[i][j] != game->player.dir_player &&
				read_cubmap[i][j] != '1' && read_cubmap[i][j] != '\n' &&
				read_cubmap[i][j] != '0' && read_cubmap[i][j] != ' ')
			{
				return_free_error("\nInvalid charachers!", game);
			}
			j++;
		}
		i++;
	}
}

void	direction(t_cub3d *game)
{
	if (game->player.dir_player == 'N')
		game->player.angle = 3 * PI / 2;
	if (game->player.dir_player == 'S')
		game->player.angle = PI / 2;
	if (game->player.dir_player == 'W')
		game->player.angle = PI;
	if (game->player.dir_player == 'E')
		game->player.angle = 2 * PI;
}

int	check_map(t_cub3d *game)
{
	int	player_count;

	player_count = check_for_player(game);
	if (player_count == 0)
		return_free_error("\nNo player found!", game);
	if (player_count != 1)
		return_free_error("\nMultiple players found!", game);
	valid_chars(game);
	make_a_copy(game);
	replace_empty_chars(game);
	if (!is_this_map_valid(game))
		return (0);
	direction(game);
	if ((WIDTH > 1700 || WIDTH < 1000)
		|| (HEIGHT > 900 || HEIGHT < 600))
		return_free_error("\nGame is incompatible with your dimensions", game);
	return (1);
}

void	init_other_data(t_cub3d *game)
{
	game->player.player = NULL;
	game->player.addr_player = NULL;
	game->player.width_player = NULL;
	game->player.height_player = NULL;
	game->player.bpp_player = NULL;
	game->player.size_line_player = NULL;
	game->player.endian_player = NULL;
}

void	init_data(t_cub3d *game, t_jeux *jeux)
{
	int	i;

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
	jeux->keys.rrotate = 0;
	jeux->keys.lrotate = 0;
	jeux->keys.up = 0;
	jeux->keys.down = 0;
	jeux->keys.right = 0;
	jeux->keys.left = 0;
	init_other_data(game);
}
