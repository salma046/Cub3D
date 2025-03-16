#include "../../cub3d.h"

void	rotate_player(t_jeux *jeux, float angle_rotation)
{
	if (jeux->keys.rrotate)
		jeux->cub.player.angle += angle_rotation;
	if (jeux->keys.lrotate)
		jeux->cub.player.angle -= angle_rotation;
}

void	move_forward_backward(t_jeux *jeux, float *x, float *y, t_movement move)
{
	if (jeux->keys.up && no_walls(*x + move.move_cos, *y + move.move_sin,
			jeux->cub.cub_map))
	{
		*x += move.move_cos;
		*y += move.move_sin;
	}
	if (jeux->keys.down && no_walls(*x - move.move_cos, *y - move.move_sin,
			jeux->cub.cub_map))
	{
		*x -= move.move_cos;
		*y -= move.move_sin;
	}
}

void	move_sideways(t_jeux *jeux, float *x, float *y, t_movement move)
{
	if (jeux->keys.right && no_walls(*x - move.move_sin, *y + move.move_cos,
			jeux->cub.cub_map))
	{
		*x -= move.move_sin;
		*y += move.move_cos;
	}
	if (jeux->keys.left && no_walls(*x + move.move_sin, *y - move.move_cos,
			jeux->cub.cub_map))
	{
		*x += move.move_sin;
		*y -= move.move_cos;
	}
}

void	move_player(t_jeux *jeux)
{
	float		angle_rotation;
	float		x_player;
	float		y_player;
	t_movement	move;

	angle_rotation = 0.05;
	x_player = jeux->cub.player.player_x;
	y_player = jeux->cub.player.player_y;
	move.move_cos = 3 * cos(jeux->cub.player.angle);
	move.move_sin = 3 * sin(jeux->cub.player.angle);
	rotate_player(jeux, angle_rotation);
	move_forward_backward(jeux, &x_player, &y_player, move);
	move_sideways(jeux, &x_player, &y_player, move);
	jeux->cub.player.player_x = x_player;
	jeux->cub.player.player_y = y_player;
}
