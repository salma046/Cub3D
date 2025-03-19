/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:22:39 by salaoui           #+#    #+#             */
/*   Updated: 2025/03/19 11:22:40 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "gnl/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define PI 3.14159265359
# define WIDTH 1300
# define HEIGHT 700
# define FRAMES 69 //78

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

typedef struct s_ray
{
	float	cos_angle;
	float	sin_angle;
	float	fb_x;
	float	fb_y;
	float	ray_x;
	float	ray_y;
	float	distance;
	float	corr_dst;
	int		march_x;
	int		march_y;
	float	ch_x;
	float	ch_y;
	int		is_vertical_hit;
	int		cast_x;
	int		cast_y;
	int		map_x;
	int		map_y;
	float	impact_x;
}					t_ray;

typedef struct s_rendering
{
	int	txt_i;
	int	txt_x;
	int	hautr_mur;
	int	dbt_pxl;
	int	fin_pxl;
}					t_rendering;

typedef struct s_player
{
	float			player_x;
	float			player_y;
	char			dir_player;
	float			angle;
	void			**player;
	int				**addr_player;
	int				*width_player;
	int				*height_player;
	int				*bpp_player;
	int				*size_line_player;
	int				*endian_player;
}					t_player;

typedef struct s_player_data
{
	int				src_index;
	int				x_start;
	int				y_start;
	unsigned int	*texture_addr;
	unsigned int	*img_addr;
	float			x_scale;
	float			y_scale;
	int				texture_x;
	int				texture_y;
	int				i;
	int				j;
}					t_player_data;

typedef struct s_render_player
{
	int				src_index;
	int				x_start;
	int				y_start;
	unsigned int	*texture_addr;
	unsigned int	*img_addr;
	float			x_scale;
	float			y_scale;
	int				texture_x;
	int				texture_y;
	int				i;
	int				j;
}					t_player_ren;

typedef enum s_enum
{
	sude,
	nord,
	ouest,
	lest,
}					t_enum;

typedef struct s_movement
{
	int				move_cos;
	int				move_sin;
}					t_movement;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				height;
	int				width;
	int				bpp;
	int				size_line;
	int				endian;
}					t_texture;

typedef struct s_cub3d
{
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	int				f_color[3];
	// unsigned int	floor_co;
	// unsigned int	ceil_co;
	int				c_color[3];
	char			**cub;
	char			**cub_map;
	char			**cub_copymap;
	int				map_heigh;
	int				map_width;
	t_texture		texture[4];
	t_texture		txt_plat;
	t_texture		txt_ciel;
	t_player		player;

}					t_cub3d;

typedef struct s_keys
{
	bool			up;
	bool			upispress;
	bool			down;
	bool			right;
	bool			left;
	bool			rrotate;
	bool			lrotate;
}					t_keys;

typedef struct s_jeux
{
	void			*win;
	void			*mlx;
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;

	t_keys			keys;

	t_cub3d			cub;
}					t_jeux;

////////////////////////////////////
/*Parsing*/
void				ft_init_text1(t_jeux *jeux, t_cub3d *game, void *mlx);
void				ft_init_text2(t_jeux *jeux, t_cub3d *game, void *mlx);
int					check_file_valid(char *file);
void				check_file(int ac, char *file);
void				init_data(t_cub3d *game, t_jeux *jeux);
void				parsing(t_cub3d *game, t_jeux *jeux);
int					check_textures(t_cub3d *game);
int					check_map(t_cub3d *game);
int					check_for_player(t_cub3d *game);
void				make_a_copy(t_cub3d *game);
char				**read_file(char *file);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				is_whitespaces(char **line);
int					ft_skipspace(char *line, int j);
int					ft_isspace(char c, int type);
int					is_empty(char *line);
char				*ft_substr(const char *s, unsigned int start, size_t len);
int					ft_my_atoi(const char *str);
char				*ft_my_strjoin(char *s1, char *s2);
void				*ft_memset(void *str, int c, size_t n);
int					split_my_elements(t_cub3d *game);
int					is_a_texture(char *line);
int					fill_cub_map(t_cub3d *game, int i);
int					parse_fc_colors(char *colorf, char *colorc, t_cub3d *game);
int					is_this_map_valid(t_cub3d *game);
void				replace_empty_chars(t_cub3d *game);

////////////////////////////////////
/*Cleaning*/
int					return_error(char *error_str);
int					return_free_error(char *error_str, t_cub3d *game);
void				ft_clean_mlx(t_jeux *jeux);

/////////////////////////////////////
/*RayCasting */
int					no_walls(float ray_x, float ray_y, char **map);
int					my_raycasting_function(t_jeux *game);
void				clear_image(t_jeux *game);
void				ft_put_pixel(int x, int y, int color, t_jeux *game);
int					handle_key_press(int key_press, t_jeux *jeux);
int					handle_key_release(int key_press, t_jeux *jeux);
int					gaming_ft(t_jeux *jeux);
void				move_player(t_jeux *jeux);
void				ft_init_text(t_jeux *jeux, t_cub3d *game, void *mlx);

/////////////////////////////////////
/*BONUS   */
int					ft_mouse(int x, int y, t_jeux *game);
void				mini_map(t_jeux *jeux);
void				parse_player_textures(t_cub3d *game, t_jeux *jeux);
void				ft_init_player(t_cub3d *game, t_jeux *jeux);
void				put_pl_hands(t_jeux *game, int *player, int texture_width,
						int texture_height);
void				fill_player_textures_1(const char **tex);
void				fill_player_textures_2(const char **tex);
void				fill_player_textures_3(const char **tex);
void				fill_player_textures_4(const char **tex);
void				ft_algo(t_ray *ray, t_rendering *render, t_jeux *game);
void				perform_dda(t_ray *ray, char **cub_map);
void				ft_soll(t_jeux *game, int i, int dbt_pxl);
int					ft_norm_ray(t_ray *ray, t_jeux *game);
void				ft_coord2(t_jeux *game, int *txt_i, int *txt_x);
void				ft_wall(t_rendering *render, t_jeux *game, int i);
void				ft_floor(t_jeux *game, int i, int fin_pxl);
int					no_walls(float ray_x, float ray_y, char **map);
void				ft_init_r(t_jeux *game, float start, t_ray *ray);
float				ft_calc_distan(t_jeux *game, t_ray *ray);
int					my_raycasting_function(t_jeux *game);
void				ft_coord(t_ray *ray, int *txt_i, int *txt_x, t_jeux *game);

void				cast_ray(t_jeux *game, float start, int i);
#endif
