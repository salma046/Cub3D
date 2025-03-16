#include "../cub3d.h"

void	ft_rota_sour(int dir, t_jeux *game, float rot)
{
	if (dir == RIGHT)
		game->cub.player.angle -= rot;
	else if (dir == LEFT)
		game->cub.player.angle += rot;
	if (game->cub.player.angle < 0)
		game->cub.player.angle += 2 * PI;
	else if (game->cub.player.angle > 2 * PI)
		game->cub.player.angle -= 2 * PI;
}

int	ft_mouse(int x, int y, t_jeux *game)
{
	static int	prch = -1;
	float		rot_vt;

	rot_vt = 0.001;
	(void)y;
	if (prch == -1)
		prch = x;
	if (prch < x)
		ft_rota_sour(LEFT, game, rot_vt * (x - prch));
	else if (prch > x)
		ft_rota_sour(RIGHT, game, rot_vt * (prch - x));
	prch = x;
	return (0);
}
