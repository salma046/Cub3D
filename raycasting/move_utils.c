#include "../cub3d.h"

int	handle_key_press(int key_press, t_jeux *jeux)
{
	int i;

	i = 0;
	if (key_press == RIGHT)
	{
		jeux->keys.rrotate = 1;
	}
	if (key_press == LEFT)
		jeux->keys.lrotate = 1;
	if (key_press == 119)
		jeux->keys.up = 1;
	if (key_press == 115)
		jeux->keys.down = 1;
	if (key_press == 100)
		jeux->keys.right = 1;
	if (key_press == 97)
		jeux->keys.left = 1;
	if (key_press == 65307)
	{
		mlx_destroy_window(jeux->mlx, jeux->win);
		mlx_destroy_image(jeux->mlx, jeux->img);
		mlx_destroy_image(jeux->mlx, jeux->cub.txt_ciel.img);
		mlx_destroy_image(jeux->mlx, jeux->cub.txt_plat.img);
		while (i < 4)
		{
			mlx_destroy_image(jeux->mlx, jeux->cub.texture[i].img);
			i++;
		}
		i = 0;
		while (i < FRAMES)
		{
			if (jeux->cub.player.player[i])
			{
				mlx_destroy_image(jeux->mlx, jeux->cub.player.player[i]);
			}
			i++;
		}
		free(jeux->cub.player.player);
		free(jeux->cub.player.addr_player);
		free(jeux->cub.player.width_player);
		free(jeux->cub.player.height_player);
		free(jeux->cub.player.bpp_player);
		free(jeux->cub.player.size_line_player);
		free(jeux->cub.player.endian_player);
		mlx_destroy_display(jeux->mlx);
		free(jeux->mlx);
		return_free_error("", &jeux->cub);
	}
	return (0);
}

int	handle_key_release(int key_press, t_jeux *jeux)
{
	if (key_press == RIGHT)
		jeux->keys.rrotate = 0;
	if (key_press == LEFT)
		jeux->keys.lrotate = 0;
	if (key_press == 119)
		jeux->keys.up = 0;
	if (key_press == 115)
		jeux->keys.down = 0;
	if (key_press == 100)
		jeux->keys.right = 0;
	if (key_press == 97)
		jeux->keys.left = 0;
	return (0);
}
void clear_image(t_jeux *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

void	move_player(t_jeux *jeux)
{
	float	angle_rotation;
	float	x_player;
	float	y_player;
	int		next_movecos;
	int		next_movesin;

	angle_rotation = 0.03;
	x_player = jeux->cub.player.player_x;
	y_player = jeux->cub.player.player_y;
	next_movecos = 4 * cos(jeux->cub.player.angle);
	next_movesin = 4 * sin(jeux->cub.player.angle);
	if (jeux->keys.rrotate)
		jeux->cub.player.angle += angle_rotation;
	if (jeux->keys.lrotate)
		jeux->cub.player.angle -= angle_rotation;

	if (jeux->keys.up && no_walls(x_player + next_movecos, y_player + next_movesin, jeux->cub.cub_map))
	{
		x_player += next_movecos;
		y_player += next_movesin;
	}
	if (jeux->keys.down && no_walls(x_player - next_movecos, y_player - next_movesin, jeux->cub.cub_map))
	{
		x_player -= next_movecos;
		y_player -= next_movesin;
	}
	if (jeux->keys.right && no_walls(x_player - next_movesin, y_player + next_movecos, jeux->cub.cub_map))
	{
		x_player -= next_movesin;
		y_player += next_movecos;
	}
	if (jeux->keys.left && no_walls(x_player + next_movesin, y_player - next_movecos, jeux->cub.cub_map))
	{
		x_player += next_movesin;
		y_player -= next_movecos;
	}
	jeux->cub.player.player_x = x_player;
	jeux->cub.player.player_y = y_player;
}

// void	init_render_player(t_data *game, t_player_ren *player,
// 		int texture_width, int texture_height)
// {
// 	player->src_index = 0;
// 	player->i = 0;
// 	player->img_addr = (unsigned int *)game->img_data;
// 	player->x_scale = (float)(texture_width - 20) / WIDTH;
// 	player->y_scale = (float)(texture_height - 20) / HEIGHT;
// }

// void	scale(t_player_ren *player, int texture_width)
// {
// 	player->texture_x = (int)(player->j * player->x_scale);
// 	player->texture_y = (int)(player->i * player->y_scale);
// 	player->src_index = player->texture_x + player->texture_y * texture_width;
// 	if (player->j >= 0 && player->j < WIDTH && player->i >= 0
// 		&& player->i < HEIGHT)
// 	{
// 		if (player->texture_addr[player->src_index] != 0xff000000)
// 		{
// 			player->img_addr[player->j + player->i
// 				* WIDTH] = player->texture_addr[player->src_index];
// 		}
// 	}
// }

// void	render1_player(t_data *game, int *player, int texture_width,
// 		int texture_height)
// {
// 	t_player_ren	*player1;

// 	player1 = ft_malloc(sizeof(t_player_ren));
// 	player1->texture_addr = (unsigned int *)player;
// 	init_render_player(game, player1, texture_width, texture_height);
// 	while (player1->i < HEIGHT)
// 	{
// 		player1->j = 0;
// 		while (player1->j < WIDTH)
// 		{
// 			scale(player1, texture_width);
// 			player1->j++;
// 		}
// 		player1->i++;
// 	}
// }

int	gaming_ft(t_jeux *jeux)
{
	move_player(jeux);
    clear_image(jeux);
	my_raycasting_function(jeux);
	// draw_map(jeux);
	mini_map(jeux);
	// ft_start(jeux);
	return (0);
}
