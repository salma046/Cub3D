#include "../cub3d.h"

// no---->1
// so---->2
// we---->3
// ea---->4
// f ---->5
// c ---->6
// map--->7


int	check_xpm_file(char *line)
{
	char *texture;
	int	i;

	i = 0;
	texture = line;
	while(texture[i] && !ft_isspace(texture[i], 0))
		i++;
	while(texture[i] && ft_isspace(texture[i], 0))
		i++;
	if (!texture[i])
		return (1);
	return (0);
}

void fix_texture(char **line)
{
	int i = 0;
	char *str;

	while (!ft_isspace((*line)[i], 0))
		i++;
	str = ft_substr((*line), 0, i);
	free(*line);
	*line = str;
}

int check_textures(t_cub3d *game)
{
	if (!check_xpm_file(game->we_texture)||
		!check_xpm_file(game->so_texture) ||
			!check_xpm_file(game->no_texture) ||
				!check_xpm_file(game->ea_texture))
	{
		return (0);
	}
	fix_texture(&game->we_texture);
	fix_texture(&game->so_texture);
	fix_texture(&game->no_texture);
	fix_texture(&game->ea_texture);
	return (1);
}

int	is_a_map(char *line)
{
	if (line[0] == '1')
		return (1);
	return (0);
}

int	is_a_texture(char *line)
{
	is_whitespaces(&line);
	if (!line || line[0] == '\0')
		return (0);
	if(!ft_strncmp(line, "NO ", 3))
		return(1);
	else if(!ft_strncmp(line, "SO ", 3))
		return(2);
	else if(!ft_strncmp(line, "WE ", 3))
		return(3);
	else if(!ft_strncmp(line, "EA ", 3))
		return(4);
	else if(!ft_strncmp(line, "F ", 2))
		return(5);
	else if(!ft_strncmp(line, "C ", 2))
		return(6);
	else if (is_a_map(line) == 1)
		return (7);
	else
		return (0);
}

int	parse_texture(t_cub3d *game, int texture_type, int i)
{
	char	**textures[6];
	char	**my_texture;
	char	*c_color = NULL;
	char	*f_color = NULL;
	int		start;

	start = ft_skipspace(game->cub[i], 3);
	textures[0] = &game->no_texture;
	textures[1] = &game->so_texture;
	textures[2] = &game->we_texture;
	textures[3] = &game->ea_texture;
	textures[4] = &f_color;
	textures[5] = &c_color;
	if (texture_type > 0 && texture_type < 7)
	{
		if (texture_type > 4)
			start = ft_skipspace(game->cub[i], 2);
		my_texture = textures[texture_type - 1];
		if (*my_texture != NULL)
			return (0);
		else
			*my_texture = ft_substr(game->cub[i], start, ft_strlen(game->cub[i]) - start);
	}
	if (parse_fc_colors(f_color, c_color, game) == 0)
		return_free_error("\nInvalid Colors!", game);
	return (1);
}

int	split_my_elements(t_cub3d *game)
{
	char **read_cub;
	int my_texture;
	int i;

	read_cub = game->cub;
	my_texture = 0;
	i = 0;
	if (!read_cub[i])
		return (0);
	while(read_cub[i])
	{
		while(read_cub[i] && !is_empty(read_cub[i]))
			i++;
		// exit(32);
		my_texture = is_a_texture(read_cub[i]);
		if (!my_texture)
			return_free_error("\nInvalid texture", game);
		else if(my_texture > 0 && my_texture < 7)
		{
			if (parse_texture(game, my_texture, i) == 0)
				return_free_error("\nInvalid textures!", game);
		}
		else
			break;
		i++;
	}
	return(fill_cub_map(game, i));
	return (1);
}
