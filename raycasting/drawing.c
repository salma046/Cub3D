#include "../cub3d.h"

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
						put_pixel(x * block_size + j, y * block_size + i, 0xf5d742, jeux);
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
