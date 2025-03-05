#include "../cub3d.h"

int ft_verf_wall(t_jeux *jeux, float new_x, float new_y, float buffer)
{
	int check_x;
	int check_y;
	float cell_center_x;
	float cell_center_y;
	float dx;
	float dy;
	float distance;
    int map_x;
    int map_y;
	int offset_x;
	int offset_y;
	
	offset_y = -1;
	map_y = (int)(new_y / 50);
	map_x = (int)(new_x / 50);
    while (offset_y <= 1) 
    {
		 offset_x = -1;
        while (offset_x <= 1) 
        {
            check_x = map_x + offset_x;
            check_y = map_y + offset_y;
            if (check_x < 0 || check_y < 0 || check_x >= WIDTH/50 || check_y >= HEIGHT/50)
                continue;  
            if (jeux->cub.cub_map[check_y][check_x] == '1' || jeux->cub.cub_map[check_y][check_x] == 'D') 
            {
                cell_center_x = (check_x * 50) + 25;
                cell_center_y = (check_y * 50) + 25;
                dx = new_x - cell_center_x;
                dy = new_y - cell_center_y;
                distance = sqrt(dx*dx + dy*dy);
                if (distance < 25 + buffer) 
                    return 0; 
            }
			offset_x++;
        }
		offset_y++;
    }
    return (1); 
}

int ft_move(t_jeux *jeux, float x, float y)
{
    float buff; 

	buff = 20.0f;
    return (ft_verf_wall(jeux, x, y, buff));
}
//---> souris
//---> gliss
//---> il reste les porte



void ft_move_player(t_jeux *jeux)
{
    float speed;
    float next_x;
    float next_y;

	speed = 3.0;
	next_x = jeux->cub.player.player_x;
	next_y = jeux->cub.player.player_y;
    if (jeux->keys.up)
    { 
        next_x += cos(jeux->cub.player.angle) * speed;
        next_y += sin(jeux->cub.player.angle) * speed;
    }
    if (jeux->keys.down)
    {
        next_x -= cos(jeux->cub.player.angle) * speed;
        next_y -= sin(jeux->cub.player.angle) * speed;
    }
    if (jeux->keys.right)
    {
        next_x += cos(jeux->cub.player.angle + PI / 2) * speed;
        next_y += sin(jeux->cub.player.angle + PI / 2) * speed;
    }
    if (jeux->keys.left)
    {
        next_x -= cos(jeux->cub.player.angle + PI / 2) * speed;
        next_y -= sin(jeux->cub.player.angle + PI / 2) * speed;
    }
	if (no_walls(next_x, jeux->cub.player.player_y, jeux->cub.cub_map))
        jeux->cub.player.player_x = next_x;
    if (no_walls(jeux->cub.player.player_x, next_y, jeux->cub.cub_map))
        jeux->cub.player.player_y = next_y;
    if (ft_move(jeux, next_x, next_y))
    {
        jeux->cub.player.player_x = next_x;
        jeux->cub.player.player_y = next_y;
    }
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
	if (key_press == 65363)
		jeux->keys.rrotate = 1;
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
	if (key_press == 101) 
        ft_porte(jeux);
	if (key_press == 65307)
	{
		mlx_destroy_window(jeux->mlx, jeux->win);
		mlx_destroy_image(jeux->mlx, jeux->img);
		mlx_destroy_display(jeux->mlx);
		free(jeux->mlx);
		return_free_error("", &jeux->cub);
	}
	ft_move_player(jeux); 
	return (0);
}
/*
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
		return_free_error("", &jeux->cub);
	}
	return (0);
}
*/

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
	x_player = jeux->cub.player.player_x;
	y_player = jeux->cub.player.player_y;
	next_movecos = 3 * cos(jeux->cub.player.angle);
	next_movesin = 3 * sin(jeux->cub.player.angle);
	if (jeux->keys.rrotate)
		jeux->cub.player.angle += angle_rotation;
	if (jeux->keys.lrotate)
		jeux->cub.player.angle -= angle_rotation;

	if (jeux->keys.up && no_walls(x_player + next_movecos, y_player + next_movesin, jeux->cub.cub_map))
	{
		x_player += next_movecos;
		y_player += next_movesin;
	}
	if (jeux->keys.down && no_walls(x_player - next_movecos, y_player - next_movesin, jeux->cub.cub_map))
	{
		x_player -= next_movecos;
		y_player -= next_movesin;
	}
	if (jeux->keys.right && no_walls(x_player - next_movesin, y_player + next_movecos, jeux->cub.cub_map))
	{
		x_player -= next_movesin;
		y_player += next_movecos;
	}
	if (jeux->keys.left && no_walls(x_player + next_movesin, y_player - next_movecos, jeux->cub.cub_map))
	{
		x_player += next_movesin;
		y_player -= next_movecos;
	}
	jeux->cub.player.player_x = x_player;
	jeux->cub.player.player_y = y_player;
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