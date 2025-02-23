#ifndef CUB3D_HPP 
#define CUB3D_HPP

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "gnl/get_next_line.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdbool.h>

# define PI 3.14159265359
# define WIDTH 1300
# define HEIGHT 700

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363


typedef struct s_player
{
	float	player_x;
	float	player_y;
	char	dir_player;
	float	angle;
}	t_player;


typedef enum s_enum
{
	sude,
	nord,
	ouest,
	lest,

}   t_enum;

typedef struct s_texture
{
    void *img;
    char *addr;
    int height;
    int width;
    int bpp;
    int size_line;
    int endian;
} t_texture;

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
	t_texture texture;
	t_player	player;

}	t_cub3d;


typedef struct s_keys
{
	bool	up;
	bool	down;
	bool	right;
	bool	left;
	bool	rrotate;
	bool	lrotate;
}	t_keys;


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
	void *img;

	char *data;
	int bpp;
	int size_line;
	int endian;

	t_keys keys;

	/*
	* il reste a faire :
	* une structure de map."t_cube3d"
	* une structure de mure.
	* une structure de joueur. 
	* une structure des ray .
	* une structure d'image. 
	*/
   t_cub3d cub;
}t_jeux;


////////////////////////////////////

int ft_start(t_jeux *jeux);
int ft_mini_map(t_jeux *jeux);
int ft_designe(int pst);
// void ft_put_pixel();
void	ft_joueur();



////////////////////////////////////
/*Parsing*/

int		check_file_valid(char *file);
void	check_file(int ac, char *file);
void	init_data(t_cub3d *game, t_jeux *jeux);
void	parsing(t_cub3d *game, t_jeux *jeux);
int		check_textures(t_cub3d *game);
int		check_map(t_cub3d *game);
int		check_for_player(t_cub3d *game);
void	make_a_copy(t_cub3d *game);
char	**read_file(char *file);
int		return_error(char *error_str);
int		return_free_error(char *error_str, t_cub3d *game);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	is_whitespaces(char **line);
int		ft_skipspace(char *line, int j);
int		ft_isspace(char c, int type);
int		is_empty(char *line);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_my_atoi(const char *str);
char	*ft_my_strjoin(char *s1, char *s2);
void	*ft_memset(void *str, int c, size_t n);
int		split_my_elements(t_cub3d *game);
int		fill_cub_map(t_cub3d *game, int i);
int		parse_fc_colors(char *colorf, char *colorc, t_cub3d *game);


/////////////////////////////////////
/*RayCasting */
//void    cast_ray(t_player *player, t_jeux *game, float start);
void cast_ray(t_jeux *game, float angle, int i);
//void cast_ray(t_jeux *game, float start, int i);
int		no_walls(float ray_x, float ray_y, char **map);
void	my_raycasting_function(t_jeux *game);
void	ft_put_pixel(int x, int y, int color, t_jeux *game);
int		handle_key_press(int key_press, t_jeux *jeux);
int		handle_key_release(int key_press, t_jeux *jeux);
int		gaming_ft(t_jeux *jeux);
void 	move_player(t_jeux *jeux);
void	draw_map(t_jeux *jeux);


/////////////////////////////////////
/*BONUS   */
void	mini_map(t_jeux *jeux);


#endif