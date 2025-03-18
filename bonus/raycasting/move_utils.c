#include "../cube3d.h"

void	ft_clean_mlx(t_jeux *jeux)
{
	int	i;

	i = 0;
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
}

void ft_porte(t_jeux *jeux)
{
    int map_x;
    int map_y;
	int dy;
	int dx;
	int check_x;
	int check_y;

	map_x = (int)(jeux->cub.player.player_x / 50);
	map_y = (int)(jeux->cub.player.player_y / 50);
	dy = -1;
    while (dy <= 1)
    {
		dx = -1;
        while (dx <= 1)
        {
            check_x = map_x + dx;
            check_y = map_y + dy;

            if (check_x < 0 || check_y < 0 || check_x >= WIDTH/50 || check_y >= HEIGHT/50)
                continue;
            if (jeux->cub.cub_map[check_y][check_x] == 'D')
            {
                jeux->cub.cub_map[check_y][check_x] = '0'; 
                return;
            }
			dx++;
        }
		dy++;
    }
}

int	handle_key_press(int key_press, t_jeux *jeux)
{
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
	if (key_press == 101) 
        ft_porte(jeux);
	if (key_press == 65307)
	{
		ft_clean_mlx(jeux);
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

void	clear_image(t_jeux *game)
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

int	gaming_ft(t_jeux *jeux)
{
	move_player(jeux);
	clear_image(jeux);
	my_raycasting_function(jeux);
	mini_map(jeux);
	return (0);
}
