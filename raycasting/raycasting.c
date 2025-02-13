#include "../cub3d.h"

int no_walls(float ray_x, float ray_y, char **map)
{
    int x = ray_x / 50;
    int y = ray_y / 50;
    if (map[y][x] == '1')
        return (0);
    return (1);
}

void    cast_ray(t_player *player, t_jeux *game, float start)
{
    float cos_angle = cos(start);
    float sin_angle = sin(start);
    float ray_x = player->player_x;
    float ray_y = player->player_y;
    // int count = 0;
    
    while (no_walls(ray_x, ray_y, game->cube.cub_map))
    {
		put_pixel(ray_x, ray_y, 0x03d3fc, game); // Draw the ray
        ray_x += cos_angle; // Move ray in x's
        ray_y += sin_angle;
        // count++;
    }
}

void my_raycasting_function(t_jeux *game)
{
    float next = (PI / 3) / 1300;
    float start = game->cube.player.angle  - (PI / 6);
    int i = 0;
    // float my_angle = atan2(190, 254);
    // float my_angle2 = atan2(270, 350);
    // printf("--new angle is: %f---and your angle is: %f\n", my_angle, my_angle2);
    while(i < 1300)
    {
        // printf("i is: %d and start += next is : %f\n", i, start += next);
        cast_ray(&game->cube.player, game, start);
        start += next;
        i++;
        // printf("i is: %d and start += next is : %f\n", i, start + next);
        // usleep(600);
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}



/// WIDTH then HEIGHT 
