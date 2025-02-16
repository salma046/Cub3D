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


void	draw_walls(int p_x, int p_y, t_jeux *jeux)
{
	// int i;
	// int j;
	int x;
	int y;

	(void)p_x;
	(void)p_y;

	// i = 0;
	// j = 0;
	y = jeux->cube.player.player_y / 50;
	// map = jeux->cube.cub_map;
	while (jeux->cube.cub_map[y])
	{
		x = jeux->cube.player.player_x / 50;
		printf("x is: %d and y is: %d\n", x, y);
		exit (8);
		while (jeux->cube.cub_map[y][x])
		{
			printf("hiiiiiii\n");
			if (jeux->cube.cub_map[y][x] == '1')
			{
				// i = 0;

				printf("the char is : %c\n", jeux->cube.cub_map[y][x]);
			}
			x++;
		}
		exit(26);
		y++;
	}
	// draw minimap
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
			if (y >= 15 && x >= 15 && y <= (map_height + 5) && x <= (map_width + 5))
			{
				ft_put_pixel(x, y, 0xd1b2b0, jeux);
			}
			else
			{
				if (y < 15 || y > (map_height + 5))
					ft_put_pixel(x, y, 0xe65a7d, jeux);
				if (x < 15 || x > (map_width + 5))
					ft_put_pixel(x, y, 0xe65a7d, jeux);
			}
			x++;
		}
		y++;
	}

	player_x = map_width / 2;
	player_y = map_height / 2;
	draw_player(player_x, player_y, 5, jeux);
	// draw_walls(player_x, player_y, jeux);

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
