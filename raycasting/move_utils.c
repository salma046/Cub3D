#include "../cub3d.h"

int	handle_key_press(int key_press, t_jeux *jeux)
{
	if (key_press == 65363)
	{
		jeux->keys.rrotate = 1;
	}
	if (key_press == 65361)
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
		return_free_error("", &jeux->cube);
	}
	return (0);
}

int	handle_key_release(int key_press, t_jeux *jeux)
{
	if (key_press == 65363)
		jeux->keys.rrotate = 0;
	if (key_press == 65361)
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
    for(int y = 0; y < 700; y++)
        for(int x = 0; x < 1300; x++)
            put_pixel(x, y, 0, game);
}

void	move_player(t_jeux *jeux)
{
	float	angle_rotation;
	int		moves;

	angle_rotation = 0.03;
	moves = 3;
	if (jeux->keys.rrotate)
		jeux->cube.player.angle += angle_rotation;
	if (jeux->keys.lrotate)
		jeux->cube.player.angle -= angle_rotation;

	if (jeux->keys.up)
	{
		jeux->cube.player.player_x += moves * cos(jeux->cube.player.angle);
		jeux->cube.player.player_y += moves * sin(jeux->cube.player.angle);
	}
	if (jeux->keys.down)
	{
		jeux->cube.player.player_x -= moves * cos(jeux->cube.player.angle);
		jeux->cube.player.player_y -= moves * sin(jeux->cube.player.angle);
	}
	if (jeux->keys.right)
	{
		jeux->cube.player.player_x -= moves * sin(jeux->cube.player.angle);
		jeux->cube.player.player_y += moves * cos(jeux->cube.player.angle);
	}
	if (jeux->keys.left)
	{
		jeux->cube.player.player_x += moves * sin(jeux->cube.player.angle);
		jeux->cube.player.player_y -= moves * cos(jeux->cube.player.angle);
	}
}


int	gaming_ft(t_jeux *jeux)
{
	move_player(jeux);
    clear_image(jeux);
	my_raycasting_function(jeux);
	draw_map(jeux);
	return (0);
}
