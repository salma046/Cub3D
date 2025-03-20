/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:27:05 by salaoui           #+#    #+#             */
/*   Updated: 2025/03/20 12:59:29 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_fc_empty(char *colorf, char *colorc, t_cub3d *game)
{
	int	i;

	i = 0;
	if (colorf != NULL)
	{
		while (i < 3)
		{
			if (game->f_color[i] != -1)
				return (free(colorf), -1);
			i++;
		}
		return (1);
	}
	i = 0;
	if (colorc != NULL)
	{
		while (i < 3)
		{
			if (game->c_color[i] != -1)
				return (free(colorc), -1);
			i++;
		}
		return (2);
	}
	return (0);
}

void	free_chunk(char **chunks, char *color)
{
	int	i;

	i = 0;
	while (chunks[i])
	{
		free(chunks[i]);
		i++;
	}
	free(color);
	free(chunks);
}

int	parce_color(char *color, int *target_color)
{
	char	**chunks;
	int		my_int;
	int		i;

	chunks = ft_split(color, ',');
	i = 0;
	while (chunks[i])
	{
		my_int = ft_my_atoi(chunks[i]);
		if (my_int < 0 || my_int > 255)
			return (free_chunk(chunks, color), 0);
		else
			target_color[i] = my_int;
		i++;
	}
	free_chunk(chunks, color);
	if (i != 3)
		return (0);
	return (1);
}

int	parse_fc_colors(char *colorf, char *colorc, t_cub3d *game)
{
	int	checker;

	if (!colorf && !colorc)
		return (1);
	checker = check_fc_empty(colorf, colorc, game);
	if (checker == 0)
		return (-1);
	if (checker == -1)
		return (0);
	if (checker == 1 && parce_color(colorf, game->f_color) == 0)
		return (0);
	if (checker == 2 && parce_color(colorc, game->c_color) == 0)
		return (0);
	if (checker == 1)
		game->floor_co = (game->f_color[0] << 16) + (game->f_color[1] << 8)
			+ game->f_color[2];
	if (checker == 2)
		game->ceil_co = (game->c_color[0] << 16) + (game->c_color[1] << 8)
			+ game->c_color[2];
	return (1);
}
