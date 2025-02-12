#include "../cub3d.h"

// int touch(float x, float y, t_jeux *game)
// {
//     (void)x;
//     (void)y;
//     (void)game;

//     // int grid_x = x / 1;
//     // int grid_y = y / 1;

//     // // Check if we hit a wall ('1' represents a wall in your map)
//     // if (game->cube.cub_map[grid_y][grid_x] == '1') 
//     //     return 1;
//     // printf("hello world\n");
//     return 0;
// }


void    cast_ray(t_player *player, t_jeux *game, float start_x, int i)
{
    (void)i;
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->player_x;
    float ray_y = player->player_y;
    int count = 0;

    // put_pixel(ray_x, ray_y, 0xFF0000, game);
    // ray_x += cos_angle;
    // ray_y += sin_angle;
    
    while (count < 300)
    {
        put_pixel(ray_x, ray_y, 0x03d3fc, game); // Draw the ray
        // printf("start x is: %f and new x is %f and new y is: %f\n", start_x, ray_x + cos_angle, ray_y + sin_angle);
        ray_x += cos_angle; // Move ray forward
        ray_y += sin_angle;
        count++;
    }
}

void my_raycasting_function(t_jeux *game)
{
    float fraction = (PI / 3) / 1300;
    float start_x = (2 * PI)  - (PI / 6);
    int i = 0;
    float my_angle = atan2(190, 254);
    float my_angle2 = atan2(270, 350);
    printf("--new angle is: %f---and your angle is: %f\n", my_angle, my_angle2);
    while(i < 1300)
    {
        // printf("i is: %d and start_x += fraction is : %f\n", i, start_x += fraction);
        cast_ray(&game->cube.player, game, start_x, i);
        start_x += fraction;
        i++;
        // printf("i is: %d and start_x += fraction is : %f\n", i, start_x + fraction);
        // usleep(600);
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}



/// WIDTH then HEIGHT 
