#include "../cub3d.h"

int no_walls(float ray_x, float ray_y, char **map)
{
    int x = ray_x / 50;
    int y = ray_y / 50;
    // if (x <= 0 || y <= 0)
    // {
    //     printf("hiiiiiiiiiiiiiiiii\n");
    //     return (0);
    //     // exit(4);
    // }
    if (map[y][x] == '1')
        return (0);
    return (1);
}

//ceci est votre algo avec la projection il fonctonne aussi

/*
void cast_ray(t_jeux *game, float angle, int i)
{
    float cos_a = cos(angle);
    float sin_a = sin(angle);
    float ray_x = game->cub.player.player_x;
    float ray_y = game->cub.player.player_y;
    float distance = 0;
    
    while (game->cub.cub_map[(int)(ray_y / 50)][(int)(ray_x / 50)] != '1') 
    {
        ray_x += cos_a;
        ray_y += sin_a;
        distance += 1;
    }
    
    int wall_height = (HEIGHT * 50) / distance;
    int start_pixel = (HEIGHT / 2) - (wall_height / 2);
    int end_pixel = (HEIGHT / 2) + (wall_height / 2);
    
    int y = start_pixel;
    while (y < end_pixel) 
    {
        if (y >= 0 && y < HEIGHT) 
        {
            game->data[y * game->size_line + i * (game->bpp / 8)] = 0xFF;
        }
        y++;
    }
}*/


/*
//apres la textute effet est nec
int ft_effet(float distance, int couleur)
{
    int a, b, c;
    float d;

    if (distance < 1) distance = 1;
    d = 1 / (1.5 * distance);

    a = (couleur >> 16) & 0xFF;
    b = (couleur >> 8) & 0xFF;
    c = couleur & 0xFF;

    a = (int)(a * d);
    b = (int)(b * d);
    c = (int)(c * d);

    if (a < 0) a = 0; if (a > 255) a = 255;
    if (b < 0) b = 0; if (b > 255) b = 255;
    if (c < 0) c = 0; if (c > 255) c = 255;

    return (a << 16) | (b << 8) | c;
}*/

void cast_ray(t_jeux *game, float start, int i)
{
    float cos_angle = cos(start);
    float sin_angle = sin(start);
    float fb_x = fabs(1 / cos_angle);
    float fb_y = fabs(1 / sin_angle);
    float ray_x = game->cub.player.player_x;
    float ray_y = game->cub.player.player_y;
    float distance = 0;
    float corr_dst;
    int march_x;
    int march_y;
    float ch_x;
    float ch_y;
    int y;
    int cast_x = (int)ray_x;
    int cast_y = (int)ray_y;

    while (game->cub.cub_map[(int)(ray_y / 50)][(int)(ray_x / 50)] != '1') 
    {
        ray_x += cos_angle;
        ray_y += sin_angle;
        distance++;
    }
    //correction de view
    corr_dst = fabs(distance * cos(start - game->cub.player.angle));
    int hautr_mur = (700 * 50) / corr_dst;
    int dbt_pxl = (700 / 2) - (hautr_mur / 2);
    int fin_pxl = (700 / 2) + (hautr_mur / 2);

    y = dbt_pxl;
    while (y < fin_pxl) 
    {
        if (y >= 0 && y < HEIGHT) 
        {
            game->data[y * game->size_line + i * (game->bpp / 8)] = 0xFF;
        }
        y++;
    }
    //dda
    if (cos_angle < 0) 
    {
        march_x = -1;
        ch_x = (game->cub.player.player_x - cast_x) * fb_x;
    } 
    else 
    {
        march_x = 1;
        ch_x = (cast_x + 1 - game->cub.player.player_x) * fb_x;
    }
    if (sin_angle < 0) {
        march_y = -1;
        ch_y = (game->cub.player.player_y - cast_y) * fb_y;
    } 
    else 
    {
        march_y = 1;
        ch_y = (cast_y + 1 - game->cub.player.player_y) * fb_y;
    }
   
    while (no_walls(cast_x,cast_y,game->cub.cub_map)) 
    {
      	if (ch_x < ch_y) 
        {
            ch_x += fb_x;
            cast_x += march_x;
        } 
        else 
        {
            ch_y += fb_y;
            cast_y += march_y;
        }
    }
}


void my_raycasting_function(t_jeux *game)
{
    float next = (PI / 3) / WIDTH;
    float start = game->cub.player.angle  - (PI / 6);
    int i = 0;
    // float my_angle = atan2(190, 254);
    // float my_angle2 = atan2(270, 350);
    // printf("--new angle is: %f---and your angle is: %f\n", my_angle, my_angle2);
	while(i < WIDTH)
	{
		// printf("i is: %d and start += next is : %f\n", i, start += next);
		cast_ray(game, start,i);
		start += next;
		i++;
		// printf("i is: %d and start += next is : %f\n", i, start + next);
		// usleep(600);
	}
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}



/// WIDTH then HEIGHT 
