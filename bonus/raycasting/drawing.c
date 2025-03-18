#include "../cube3d.h"

void	draw_player(int player_x, int player_y, int diametre, t_jeux *jeux)
{
	int	x;
	int	y;

	x = diametre - player_x;
	while (x < diametre + player_x)
	{
		y = diametre - player_y;
		while (y < diametre + player_y)
		{
			if (((y - player_y) * (y - player_y) + (x - player_x) * (x
						- player_x)) <= diametre * diametre)
				ft_put_pixel(x, y, 0x51f5d9, jeux);
			y++;
		}
		x++;
	}
}

int	check_distance(int mini_x, int mini_y, int wall_y, int wall_x, t_jeux *jeux,
		int color)
{
	int	p_y;
	int	p_x;
	int	i;
	int	j;
	int	new_wallx;
	int	new_wally;

	p_y = jeux->cub.player.player_y / 50;
	p_x = jeux->cub.player.player_x / 50;
	if (abs(p_y - wall_y) <= 7 && abs(p_x - wall_x) <= 13)
	{
		new_wallx = mini_x + ((wall_x - p_x) * 20);
		new_wally = mini_y + ((wall_y - p_y) * 20);
		i = 0;
		while (i < 20)
		{
			j = 0;
			while (j < 20)
			{
				if (((new_wallx + j) <= (WIDTH / 5) + 5 && (new_wallx
							+ j) >= 15)
					&& ((new_wally + i) <= (HEIGHT / 5) + 5 && (new_wally
							+ i >= 15)))
				{
					ft_put_pixel(new_wallx + j, new_wally + i, color, jeux);
				}
				j++;
			}
			i++;
		}
	}
	return (0);
}

void	draw_walls(int p_x, int p_y, t_jeux *jeux)
{
	int	i;
	int	j;

	i = 0;
	while (jeux->cub.cub_map[i])
	{
		j = 0;
		while (jeux->cub.cub_map[i][j])
		{
			if (jeux->cub.cub_map[i][j] == '1'
				|| jeux->cub.cub_map[i][j] == 'D')
				check_distance(p_x, p_y, i, j, jeux, 0x3291a8);
			if (jeux->cub.cub_map[i][j] == '0'
				|| jeux->cub.cub_map[i][j] == jeux->cub.player.dir_player)
				check_distance(p_x, p_y, i, j, jeux, 0xd1b2b0);
			j++;
		}
		i++;
	}
}

void	mini_map(t_jeux *jeux)
{
	int	map_width;
	int	map_height;
	int	player_x;
	int	player_y;

	map_width = WIDTH / 5;
	map_height = HEIGHT / 5;
	player_x = map_width / 2;
	player_y = map_height / 2;
	draw_walls(player_x, player_y, jeux);
	draw_player(player_x, player_y, 5, jeux);
}
