/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibahouch <ibahouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:27:05 by salaoui           #+#    #+#             */
/*   Updated: 2025/03/21 07:24:25 by ibahouch         ###   ########.fr       */
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

int	parce_color(char *color, int *target_color)
{
	int		i;
	int		j;
	int		count;
	char	my_color[5];
	int		my_int;

	i = 0;
	j = 0;
	count = 0;
	while (color[count] != '\0' && i < 3)
	{
		j = 0;
		while (color[count] != '\0' && color[count] != ',' && j <= 3)
			my_color[j++] = color[count++];
		if (color[count] == ',')
			count++;
		my_color[j] = '\0';
		my_int = ft_my_atoi(my_color);
		if (my_int < 0 || my_int > 255)
			return (free(color), 0);
		target_color[i++] = my_int;
	}
	if (color[count] == '\0' && i == 4)
		return (free(color), 0);
	return (free(color), 1);
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
