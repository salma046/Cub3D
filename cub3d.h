#ifndef CUB3D_HPP 
#define CUB3D_HPP

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "gnl/get_next_line.h"
#include <mlx.h>

typedef struct s_cub3d
{
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;
    int     f_color[3];
    int		c_color[3];
    char    **cub_map;
    char    **cub;
    int     map_heigh;
    int     map_width;


}   t_cub3d;


int     check_file_valid(char *file);
int     return_error(char *error_str);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);

#endif