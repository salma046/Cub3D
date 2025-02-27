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

void ft_init_text(t_cub3d *game,void *mlx)
{
    char *text[4]= {"texture/ff.xpm","texture/ff.xpm","texture/ff.xpm","texture/ff.xpm"};
    char *pl = "texture/44.xpm";
    char *cl = "texture/cl.xpm";
    int i = 0;

 
    if (!mlx)
        return_error("mlx non initialisé !");
   while(i < 4)
    {
        game->texture[i].img = mlx_xpm_file_to_image(mlx,text[i],&game->texture[i].width,&game->texture[i].height);
        if(!game->texture[i].img)
            return_error("**********erreur");
        game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,&game->texture[i].bpp, &game->texture[i].size_line, &game->texture[i].endian);
        i++;
    }    
    game->txt_plat.img = mlx_xpm_file_to_image(mlx, pl, &game->txt_plat.width, &game->txt_plat.height);
    game->txt_plat.addr = mlx_get_data_addr(game->txt_plat.img, &game->txt_plat.bpp, &game->txt_plat.size_line, &game->txt_plat.endian);
    game->txt_ciel.img = mlx_xpm_file_to_image(mlx, cl, &game->txt_ciel.width, &game->txt_ciel.height);
    if(!game->txt_plat.img || !game->txt_ciel.img)
        return_error("-----------------erreur");
    game->txt_ciel.addr = mlx_get_data_addr(game->txt_ciel.img, &game->txt_ciel.bpp, &game->txt_ciel.size_line, &game->txt_ciel.endian);
}


void ft_init_r(t_jeux *game, float start, float *cos_angle, float *sin_angle, float *fb_x, float *fb_y, float *ray_x, float *ray_y)
{
    *cos_angle = cos(start);
    *sin_angle = sin(start);
    *fb_x = fabs(1 / *cos_angle);
    *fb_y = fabs(1 / *sin_angle);
    *ray_x = game->cub.player.player_x;
    *ray_y = game->cub.player.player_y;
}

// Calculate distance a wall
float ft_calc_distan(t_jeux *game, float *ray_x, float *ray_y, float cos_angle, float sin_angle)
{
    float distance; 
    
    distance = 0;
    while (game->cub.cub_map[(int)(*ray_y / 50)][(int)(*ray_x / 50)] != '1') 
    {
        *ray_x += cos_angle;
        *ray_y += sin_angle;
        int map_x = (int)(*ray_x / 50);
        int map_y = (int)(*ray_y / 50);
        if (map_x < 0 || map_y < 0 || map_x >= WIDTH || map_y >= HEIGHT) 
            break; 
        distance++;
    }
    return (distance);
}

void ft_algo(float cos_angle, float sin_angle, int *march_x, int *march_y, float *ch_x, float *ch_y, int *cast_x, int *cast_y, float player_x, float player_y)
{
    if (cos_angle < 0) 
    {
        *march_x = -1;
        *ch_x = (player_x - *cast_x) * fabs(1 / cos_angle);
    } 
    else 
    {
        *march_x = 1;
        *ch_x = (*cast_x + 1 - player_x) * fabs(1 / cos_angle);
    }
    
    if (sin_angle < 0) {
        *march_y = -1;
        *ch_y = (player_y - *cast_y) * fabs(1 / sin_angle);
    } 
    else 
    {
        *march_y = 1;
        *ch_y = (*cast_y + 1 - player_y) * fabs(1 / sin_angle);
    }
}

void perform_dda(int *cast_x, int *cast_y, float *ch_x, float *ch_y, float fb_x, float fb_y, int march_x, int march_y, int *is_vertical_hit, char **cub_map)
{
    while (no_walls(*cast_x, *cast_y, cub_map)) 
    {
        if (*ch_x < *ch_y) 
        {
            *ch_x += fb_x;
            *cast_x += march_x;
            *is_vertical_hit = 1; // mure vertical
        } 
        else 
        {
            *ch_y += fb_y;
            *cast_y += march_y;
            *is_vertical_hit = 0; // muer horizontal
        }
        if (*ch_x > 10000 || *ch_y > 10000) 
        {
            break;
        }
    }
}

void ft_soll(t_jeux *game, int i, int dbt_pxl)
{
    int y;
    int txt_x;
    int txt_y;
    int coll;

    y = 0;
    while (y < dbt_pxl) 
    {
        txt_x = (i * game->cub.txt_ciel.width) / WIDTH;
        txt_y = (y * game->cub.txt_ciel.height) / (HEIGHT / 2);
        
        coll = *(int *)(game->cub.txt_ciel.addr 
                    + (txt_y * game->cub.txt_ciel.size_line + txt_x * (game->cub.txt_ciel.bpp / 8)));
        
        *(int *)(game->data + (y * game->size_line + i * (game->bpp / 8))) = coll;
        y++;
    }
}

void ft_coord(int is_vertical_hit, int march_x, int march_y, float ray_x, float ray_y, int *txt_i, int *txt_x, t_jeux *game)
{
    float impact_x;

    if (is_vertical_hit)
    {
        if (march_x == 1)
            *txt_i = 0; // mure est
        else
            *txt_i = 1; // mure ouest
    }  
    else 
    {
        if (march_y == 1)
            *txt_i = 2; // mure sude
        else
            *txt_i = 3; // mure nord
    }
    if (is_vertical_hit)
        impact_x = ray_y;
    else
        impact_x = ray_x;
    impact_x = fmod(impact_x, 50);
    *txt_x = (int)((impact_x / 50.0) * (game->cub.texture[*txt_i].width - 1));
    if (*txt_x < 0) 
        *txt_x = 0;
    if (*txt_x >= game->cub.texture[*txt_i].width) 
        *txt_x = game->cub.texture[*txt_i].width - 1;
}

void ft_wall(t_jeux *game, int i, int dbt_pxl, int fin_pxl, int hautr_mur, int txt_i, int txt_x)
{
    int y;
    int txt_y;
    int coll;

    y = dbt_pxl;
    while (y < fin_pxl) 
    {
        txt_y = ((y - dbt_pxl) * game->cub.texture[txt_i].height) / hautr_mur;

        if (txt_x >= 0 && txt_x < game->cub.texture[txt_i].width &&
            txt_y >= 0 && txt_y < game->cub.texture[txt_i].height) 
        {
            coll = *(int *)(game->cub.texture[txt_i].addr 
                        + (txt_y * game->cub.texture[txt_i].size_line + txt_x * (game->cub.texture[txt_i].bpp / 8)));
            if (y >= 0 && y < HEIGHT) 
            {
                *(int *)(game->data + (y * game->size_line + i * (game->bpp / 8))) = coll;
            }
        }
        y++;
    }
}

// Render floor
void ft_floor(t_jeux *game, int i, int fin_pxl)
{
    int y;
    int txt_x;
    int txt_y;
    int coll;

    y = fin_pxl;
    while(y < HEIGHT)
    {
        txt_x = (i * game->cub.txt_plat.width) / WIDTH;
        txt_y = ((y - HEIGHT / 2) * game->cub.txt_plat.height) / (HEIGHT / 2);

        if (txt_x >= 0 && txt_x < game->cub.txt_plat.width &&
            txt_y >= 0 && txt_y < game->cub.txt_plat.height)
        {
            coll = *(int *)(game->cub.txt_plat.addr 
                        + (txt_y * game->cub.txt_plat.size_line + txt_x * (game->cub.txt_plat.bpp / 8)));
            *(int *)(game->data + (y * game->size_line + i * (game->bpp / 8))) = coll;
        }
        y++;
    }
}

void cast_ray(t_jeux *game, float start, int i)
{
    float cos_angle, sin_angle, fb_x, fb_y, ray_x, ray_y;
    float distance, corr_dst;
    int march_x, march_y;
    float ch_x, ch_y;
    int is_vertical_hit;
    int txt_i, txt_x;
    int cast_x;
    int cast_y;
    int hautr_mur;
    int dbt_pxl;
    int fin_pxl;

    ft_init_r(game, start, &cos_angle, &sin_angle, &fb_x, &fb_y, &ray_x, &ray_y);
    cast_x = (int)ray_x;
    cast_y = (int)ray_y;
    distance = ft_calc_distan(game, &ray_x, &ray_y, cos_angle, sin_angle);
    corr_dst = fabs(distance * cos(start - game->cub.player.angle));
    hautr_mur = (700 * 50) / corr_dst;
    dbt_pxl = (700 / 2) - (hautr_mur / 2);
    fin_pxl = (700 / 2) + (hautr_mur / 2);
    ft_algo(cos_angle, sin_angle, &march_x, &march_y, &ch_x, &ch_y, 
              &cast_x, &cast_y, game->cub.player.player_x, game->cub.player.player_y);
    perform_dda(&cast_x, &cast_y, &ch_x, &ch_y, fb_x, fb_y, 
               march_x, march_y, &is_vertical_hit, game->cub.cub_map);
    ft_soll(game, i, dbt_pxl);
    ft_coord(is_vertical_hit, march_x, march_y, ray_x, ray_y, &txt_i, &txt_x, game);
    ft_wall(game, i, dbt_pxl, fin_pxl, hautr_mur, txt_i, txt_x);
    ft_floor(game, i, fin_pxl);
}

/*

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
        int map_x = (int)(ray_x / 50);
        int map_y = (int)(ray_y / 50);
        if (map_x < 0 || map_y < 0 || map_x >= WIDTH || map_y >= HEIGHT) 
        {
            break; 
        }
        distance++;
    }
    //correction de view
    corr_dst = fabs(distance * cos(start - game->cub.player.angle));
    int hautr_mur = (700 * 50) / corr_dst;
    int dbt_pxl = (700 / 2) - (hautr_mur / 2);
    int fin_pxl = (700 / 2) + (hautr_mur / 2);

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
   
	int is_vertical_hit;
    while (no_walls(cast_x,cast_y,game->cub.cub_map)) 
    {
        if (ch_x < ch_y) 
        {
            ch_x += fb_x;
            cast_x += march_x;
            is_vertical_hit = 1; // Murlllllll vertical*********
        } 
        else 
        {
            ch_y += fb_y;
            cast_y += march_y;
            is_vertical_hit = 0; // Murllllllll horizontal*********
}
        if (ch_x > 10000 || ch_y > 10000) 
        {
            break;
        }

    }
     //le ciel
    // Rendu du ciel
    y = 0;
    while (y < dbt_pxl) 
    {
        int txt_x = (i * game->cub.txt_ciel.width) / WIDTH; // Ajout de txt_x
        int txt_y = (y * game->cub.txt_ciel.height) / (HEIGHT / 2);
        
        int coll = *(int *)(game->cub.txt_ciel.addr 
                    + (txt_y * game->cub.txt_ciel.size_line + txt_x * (game->cub.txt_ciel.bpp / 8)));
        
        *(int *)(game->data + (y * game->size_line + i * (game->bpp / 8))) = coll; // Affectation correcte
        y++;
    }

    int txt_i;
    if (is_vertical_hit)
    {
        if (march_x == 1)
            txt_i = 0; // Mur Est
        else
            txt_i = 1; // Mur Ouest
    }  
    else 
    {
        if (march_y == 1)
            txt_i = 2; // Mur Sud
        else
            txt_i = 3; // Mur Nord
    }



    float impact_x;
    if (is_vertical_hit)
        impact_x = ray_y;
    else
        impact_x = ray_x;
    impact_x = fmod(impact_x, 50);
    int txt_x = (int)((impact_x / 50.0) * (game->cub.texture[txt_i].width - 1));
   // int txt_x = (int)(impact_x / 50.0 * game->cub.texture[txt_i].width);
    
    if (txt_x < 0) 
        txt_x = 0;
    if (txt_x >= game->cub.texture[txt_i].width) 
        txt_x = game->cub.texture[txt_i].width - 1;
    // Rendu des murs
    y = dbt_pxl;
    while (y < fin_pxl) 
    {
        int txt_y = ((y - dbt_pxl) * game->cub.texture[txt_i].height) / hautr_mur;

        if (txt_x >= 0 && txt_x < game->cub.texture[txt_i].width &&
            txt_y >= 0 && txt_y < game->cub.texture[txt_i].height) 
        {
            int coll = *(int *)(game->cub.texture[txt_i].addr 
                        + (txt_y * game->cub.texture[txt_i].size_line + txt_x * (game->cub.texture[txt_i].bpp / 8)));

            if (y >= 0 && y < HEIGHT) 
            {
                *(int *)(game->data + (y * game->size_line + i * (game->bpp / 8))) = coll;
            }
        }
        y++;
    }

    //les platform
    while(y < HEIGHT)
    {
        int txt_x = (i * game->cub.txt_plat.width) / WIDTH;
        int txt_y = ((y - HEIGHT / 2) * game->cub.txt_plat.height) / (HEIGHT / 2);

        if (txt_x >= 0 && txt_x < game->cub.txt_plat.width &&
            txt_y >= 0 && txt_y < game->cub.txt_plat.height)
        {
            int coll = *(int *)(game->cub.txt_plat.addr 
                        + (txt_y * game->cub.txt_plat.size_line + txt_x * (game->cub.txt_plat.bpp / 8)));
            *(int *)(game->data + (y * game->size_line + i * (game->bpp / 8))) = coll;
        }

        // int txt_y = ((y - HEIGHT / 2) * game->cub.txt_plat.height) / (HEIGHT / 2);
        
        // int coll = *(int *)(game->cub.txt_plat.addr + (txt_y * game->cub.txt_plat.size_line));
        // game->data[y * game->size_line + i * (game->bpp / 8)] = coll;
        y++;
    }
}
*/

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
