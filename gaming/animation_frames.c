#include "../cub3d.h"

void	player_data(t_jeux *game, t_player_data *player,
		int texture_width, int texture_height)
{
	player->src_index = 0;
	player->i = 0;
	player->img_addr = (unsigned int *)game->data;
	player->x_scale = (float)(texture_width - 20) / WIDTH;
	player->y_scale = (float)(texture_height - 20) / HEIGHT;
}


void	scale(t_player_data *player, int texture_width)
{
	player->texture_x = (int)(player->j * player->x_scale);
	player->texture_y = (int)(player->i * player->y_scale);
	player->src_index = player->texture_x + player->texture_y * texture_width;
	if (player->j >= 0 && player->j < WIDTH && player->i >= 0
		&& player->i < HEIGHT)
	{
		if (player->texture_addr[player->src_index] != 0xff000000)
		{
			player->img_addr[player->j + player->i
				* WIDTH] = player->texture_addr[player->src_index];
		}
	}
}

void	put_pl_hands(t_jeux *game, int *player, int texture_width,
		int texture_height)
{
	t_player_data	*player1;

	player1 = malloc(sizeof(t_player_data));
	if (!player1)
		return;
	player1->texture_addr = (unsigned int *)player;
	player_data(game, player1, texture_width, texture_height);
	while (player1->i < HEIGHT)
	{
		player1->j = 0;
		while (player1->j < WIDTH)
		{
			scale(player1, texture_width);
			player1->j++;
		}
		player1->i++;
	}
	free(player1);
}
