/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:22:32 by salaoui           #+#    #+#             */
/*   Updated: 2025/03/19 11:22:34 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	return_error(char *error_str)
{
	printf("Error: %s\n", error_str);
	exit(0);
}

int	second_free_error(t_cub3d *game)
{
	int	i;

	i = 0;
	while (game->cub_map && game->cub_map[i])
	{
		free(game->cub_map[i++]);
	}
	free(game->cub_map);
	i = 0;
	while (game->cub_copymap && game->cub_copymap[i])
	{
		free(game->cub_copymap[i++]);
	}
	free(game->cub_copymap);
	return (0);
}

int	return_free_error(char *error_str, t_cub3d *game)
{
	char	**temp;
	int		i;

	i = 0;
	temp = game->cub;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
	if (game->no_texture)
		free(game->no_texture);
	if (game->so_texture)
		free(game->so_texture);
	if (game->we_texture)
		free(game->we_texture);
	if (game->ea_texture)
		free(game->ea_texture);
	if (error_str[0] != '\0')
		printf("Error: %s\n", error_str);
	second_free_error(game);
	exit(0);
}
