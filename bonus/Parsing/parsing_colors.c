/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:32:24 by salaoui           #+#    #+#             */
/*   Updated: 2025/03/19 11:32:25 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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
	char	my_color[4];
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
	if (color[count] == '\0' && i == 3)
		return (free(color), 1);
	return (free(color), 0);
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
	return (1);
}
