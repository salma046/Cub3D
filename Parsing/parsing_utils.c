#include "../cub3d.h"

void	initialize_textures(t_cub3d *game, char ***textures, char **f_color,
		char **c_color)
{
	textures[0] = &game->no_texture;
	textures[1] = &game->so_texture;
	textures[2] = &game->we_texture;
	textures[3] = &game->ea_texture;
	textures[4] = f_color;
	textures[5] = c_color;
}

int	determine_start_index(char *line, int texture_type)
{
	if (texture_type > 4)
		return (ft_skipspace(line, 2));
	return (ft_skipspace(line, 3));
}

int	assign_texture(char *cub, char ***textures, int texture_type, int start)
{
	char	**my_texture;

	if (texture_type < 1 || texture_type > 6)
		return (1);
	my_texture = textures[texture_type - 1];
	if (*my_texture != NULL)
		return (0);
	*my_texture = ft_substr(cub, start, ft_strlen(cub)
			- start);
	return (1);
}

int	parse_texture(t_cub3d *game, int texture_type, int i)
{
	char	*c_color;
	char	*f_color;
	char	**textures[6];
	int		start;

	c_color = NULL;
	f_color = NULL;
	initialize_textures(game, textures, &f_color, &c_color);
	start = determine_start_index(game->cub[i], texture_type);
	if (!assign_texture(game->cub[i], textures, texture_type, start))
		return (0);
	if (!parse_fc_colors(f_color, c_color, game))
		return_free_error("\nInvalid Colors!", game);
	return (1);
}

int	split_my_elements(t_cub3d *game)
{
	char	**read_cub;
	int		my_texture;
	int		i;

	read_cub = game->cub;
	my_texture = 0;
	i = 0;
	if (!read_cub[i])
		return (0);
	while (read_cub[i++])
	{
		while (read_cub[i] && !is_empty(read_cub[i]))
			i++;
		my_texture = is_a_texture(read_cub[i]);
		if (!my_texture)
			return_free_error("\nInvalid texture", game);
		else if (my_texture > 0 && my_texture < 7)
		{
			if (parse_texture(game, my_texture, i) == 0)
				return_free_error("\nInvalid textures!", game);
		}
		else
			break ;
	}
	return (fill_cub_map(game, i));
}
