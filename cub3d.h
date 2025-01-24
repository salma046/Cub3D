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
char	**read_file(char *file);
int     return_error(char *error_str);
int     return_free_error(char *error_str, t_cub3d *game);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int     ft_my_atoi(const char *str);
int     split_my_elements(t_cub3d *game);
int     fill_cub_map(t_cub3d *game, int i);
int     parse_fc_colors(char *colorf, char *colorc, t_cub3d *game);

#endif