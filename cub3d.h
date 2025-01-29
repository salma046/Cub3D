#ifndef CUB3D_HPP 
#define CUB3D_HPP

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "gnl/get_next_line.h"
#include <mlx.h>



typedef struct s_player
{
	int		player_x;
	int		player_y;
	char	dir_player;

}	t_player;


typedef enum s_enum
{
    sude,
    nord,
    ouest,
    lest,

}   t_enum;


typedef struct s_cub3d
{
    char	*no_texture;
    char	*so_texture;
    char	*we_texture;
    char	*ea_texture;
    int		f_color[3];
    int		c_color[3];
    char	**cub;
    char	**cub_map;
    char	**cub_copymap;
    int		map_heigh;
    int		map_width;
    t_player	player;

}   t_cub3d;

typedef struct s_jeux
{
    //la position de joueur dans la carte.
    float x_pst;
    float y_pst;
    //les coordonnees de vision de camera,
    float x_cam;
    float y_cam;
    //encore les coordonnees dechaque direction. 
    float x_direct;
    float y_direct;
    //les coordonnees des ray de ratcasting
    float x_ray;
    float y_ray;
    //chaine pour les donnees
    char *str;
    //pointeur de fenetre et mlx
    void *win;
    void *mlx;
    /*
    * il reste a faire :
    * une structure de map."t_cube3d"
    * une structure de mure.
    * une structure de joueur. 
    * une structure des ray .
    * une structure d'image. 
    */
   t_cub3d cube;
}t_jeux;


////////////////////////////////////

int ft_start(t_jeux *jeux);
int ft_mini_map(t_jeux *jeux);
int ft_designe(int pst);
void ft_put_pexel();
void    ft_joueur();



////////////////////////////////////
/*Parsing*/

int     check_file_valid(char *file);
char	**read_file(char *file);
int     return_error(char *error_str);
int     return_free_error(char *error_str, t_cub3d *game);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
void    is_whitespaces(char **line);
int     ft_skipspace(char *line);
int     ft_isspace(char c, int type);
int     is_empty(char *line);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int     ft_my_atoi(const char *str);
char	*ft_my_strjoin(char *s1, char *s2);
void	*ft_memset(void *str, int c, size_t n);
int     split_my_elements(t_cub3d *game);
int     fill_cub_map(t_cub3d *game, int i);
int     parse_fc_colors(char *colorf, char *colorc, t_cub3d *game);

#endif