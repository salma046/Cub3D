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
		mlx_destroy_image(jeux->mlx, jeux->img);
		mlx_destroy_display(jeux->mlx);
		free(jeux->mlx);
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
	x_player = jeux->cube.player.player_x;
	y_player = jeux->cube.player.player_y;
	next_movecos = 3 * cos(jeux->cube.player.angle);
	next_movesin = 3 * sin(jeux->cube.player.angle);
	if (jeux->keys.rrotate)
		jeux->cube.player.angle += angle_rotation;
	if (jeux->keys.lrotate)
		jeux->cube.player.angle -= angle_rotation;

	if (jeux->keys.up && no_walls(x_player + next_movecos, y_player + next_movesin, jeux->cube.cub_map))
	{
		x_player += next_movecos;
		y_player += next_movesin;
	}
	if (jeux->keys.down && no_walls(x_player - next_movecos, y_player - next_movesin, jeux->cube.cub_map))
	{
		x_player -= next_movecos;
		y_player -= next_movesin;
	}
	if (jeux->keys.right && no_walls(x_player - next_movesin, y_player + next_movecos, jeux->cube.cub_map))
	{
		x_player -= next_movesin;
		y_player += next_movecos;
	}
	if (jeux->keys.left && no_walls(x_player + next_movesin, y_player - next_movecos, jeux->cube.cub_map))
	{
		x_player += next_movesin;
		y_player -= next_movecos;
	}
	jeux->cube.player.player_x = x_player;
	jeux->cube.player.player_y = y_player;
}


int	gaming_ft(t_jeux *jeux)
{
	move_player(jeux);
    clear_image(jeux);
	my_raycasting_function(jeux);
	draw_map(jeux);
	mini_map(jeux);
	// ft_start(jeux);
	return (0);
}
