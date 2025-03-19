/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:32:32 by salaoui           #+#    #+#             */
/*   Updated: 2025/03/19 11:32:33 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

// no---->1
// so---->2
// we---->3
// ea---->4
// f ---->5
// c ---->6
// map--->7

int	check_xpm_file(char *line)
{
	char	*texture;
	int		i;

	i = 0;
	texture = line;
	while (texture[i] && !ft_isspace(texture[i], 0))
		i++;
	while (texture[i] && ft_isspace(texture[i], 0))
		i++;
	if (!texture[i])
		return (1);
	return (0);
}

void	fix_texture(char **line, t_cub3d *game)
{
	int		i;
	char	*str;
	int		fd;

	i = 0;
	while (!ft_isspace((*line)[i], 0))
		i++;
	str = ft_substr((*line), 0, i);
	free(*line);
	*line = str;
	fd = open((*line), O_RDONLY);
	if (fd == -1)
		return_free_error("\nwrong textures!", game);
	else
		close(fd);
}

int	check_textures(t_cub3d *game)
{
	if (!check_xpm_file(game->we_texture) || !check_xpm_file(game->so_texture)
		|| !check_xpm_file(game->no_texture)
		|| !check_xpm_file(game->ea_texture))
	{
		return (0);
	}
	fix_texture(&game->we_texture, game);
	fix_texture(&game->so_texture, game);
	fix_texture(&game->no_texture, game);
	fix_texture(&game->ea_texture, game);
	return (1);
}

int	is_a_map(char *line)
{
	if (line[0] == '1' || line[0] == 'D')
		return (1);
	return (0);
}

int	is_a_texture(char *line)
{
	is_whitespaces(&line);
	if (!line || line[0] == '\0')
		return (0);
	if (!ft_strncmp(line, "NO ", 3))
		return (1);
	else if (!ft_strncmp(line, "SO ", 3))
		return (2);
	else if (!ft_strncmp(line, "WE ", 3))
		return (3);
	else if (!ft_strncmp(line, "EA ", 3))
		return (4);
	else if (!ft_strncmp(line, "F ", 2))
		return (5);
	else if (!ft_strncmp(line, "C ", 2))
		return (6);
	else if (is_a_map(line) == 1)
		return (7);
	else
		return (0);
}
