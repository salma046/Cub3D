#include "../cub3d.h"


void	draw_player(int player_x, int player_y, int diametre, t_jeux *jeux)
{
	int x;
	int y;

	x = diametre - player_x;
	while (x < diametre + player_x)
	{
		y = diametre - player_y;
		while (y < diametre + player_y)
		{
			if (((y - player_y) * (y - player_y) + (x - player_x) * (x - player_x)) <= diametre * diametre)
				ft_put_pixel(x, y, 0x51f5d9, jeux);
			y++;
		}
		x++;
		
	}
}

int check_edge(int y, int x, t_jeux *jeux)
{
	char **map;

	map = jeux->cube.cub_copymap;
	if (y == 0 || map[y + 1] == NULL)
		return (3);
	if (map[y - 1][x] == '\0' || map[y + 1][x] == '\0')
		return (1);
	if (map[y][x - 1] == '\0' || map[y][x + 1] == '\0')
		return (1);
	return (0);
}

void	fill_colors( int posx, int posy, t_jeux *jeux)
{
	int i;
	// int j;
	int start;

	start = 15;
	while (start < posx)
	{
		i = 0;
		while (i < 20)
		{
			ft_put_pixel(start, posy + i, 0x00FF00, jeux);
			i++;
		}
		start++;
	}	
}

int	check_distance(int mini_x, int mini_y, int wall_y, int wall_x, t_jeux *jeux, int color)
{
	int p_y;
	int p_x;
	int i;
	int j;
	int new_wallx;
	int new_wally;

	p_y = jeux->cube.player.player_y / 50;
	p_x = jeux->cube.player.player_x / 50;
	if (abs(p_y - wall_y) <= 7 && abs(p_x - wall_x) <= 13)
	{
		new_wallx = mini_x +((wall_x - p_x) * 20);
		new_wally = mini_y +((wall_y - p_y) * 20);
		i = 0;
		while (i < 20)
		{
			j = 0;
			while (j < 20)
			{
				if (((new_wallx + j) <= (WIDTH / 5) + 5 && (new_wallx + j) >= 15) &&
						((new_wally + i) <= (HEIGHT / 5) + 5 && (new_wally + i >= 15)))
				{
					ft_put_pixel(new_wallx + j, new_wally + i, color, jeux);
					// if (check_edge(wall_y, wall_x, jeux) == 3)
					// 	fill_colors(new_wallx, new_wally, jeux);

				}
				j++;
			}
			i++;
		}
		// 	exit (43);
			// draw_empty_space()
	}
	return (0);
}

void	draw_walls(int p_x, int p_y, t_jeux *jeux)
{
	int i;
	int j;
	// int x;
	// int y;


	i = 0;
	while (jeux->cube.cub_map[i])
	{
		j = 0;
		while (jeux->cube.cub_map[i][j])
		{
			if (jeux->cube.cub_map[i][j] == '1')
			{
				check_distance(p_x, p_y, i, j, jeux, 0x3291a8);
					// draw_minimap();
			}
			if (jeux->cube.cub_map[i][j] == '0' || jeux->cube.cub_map[i][j] == jeux->cube.player.dir_player)
			{
				check_distance(p_x, p_y, i, j, jeux, 0xd1b2b0);
					// draw_minimap();
			}
			j++;
		}
		// printf("%s", jeux->cube.cub_map[i]);
		i++;
	}
}

void	mini_map(t_jeux *jeux)
{
	int map_width;
	int map_height;
	int player_x;
	int player_y;
	int x;
	int y;

	map_width = WIDTH / 5;
	map_height = HEIGHT / 5;
	y = 10;

	while (y < (map_height + 10))
	{
		x = 10;
		while (x < (map_width + 10))
		{
			// if (y >= 15 && x >= 15 && y <= (map_height + 5) && x <= (map_width + 5))
			// {
			// 	ft_put_pixel(x, y, 0xd1b2b0, jeux);
			// }
			// else
			// {
			// if (y < 15 || y > (map_height + 5))
			// 	ft_put_pixel(x, y, 0xe65a7d, jeux);
			// if (x < 15 || x > (map_width + 5))
			// 	ft_put_pixel(x, y, 0xe65a7d, jeux);
			// // }
			x++;
		}
		y++;
	}

	player_x = map_width / 2;
	player_y = map_height / 2;
	draw_walls(player_x, player_y, jeux);
	draw_player(player_x, player_y, 5, jeux);

}

void	draw_map(t_jeux *jeux)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		block_size;
	char	**map;

	y = 0;
	block_size = 50;
	map = jeux->cube.cub_map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				i = 0;
				while (i < block_size)
				{
					j = 0;
					while (j < block_size)
					{
						ft_put_pixel(x * block_size + j, y * block_size + i, 0xf5d742, jeux);
						j++;
					}
					i++;
				}
			}
			x++;
		}
		y++;
	}
}
