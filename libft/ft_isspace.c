/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 21:21:40 by salaoui           #+#    #+#             */
/*   Updated: 2025/01/26 09:52:02 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c, int type)
{
	if (type == 1)
	{
		return (c == ' ' || c == '\t' ||c == '\v' ||
			c == '\f' || c == '\r');
	}
	else
	{
		return (c == ' ' || c == '\t' || c == '\n' ||
				c == '\v' || c == '\f' || c == '\r');
	}
}

int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i], 0))
		i++;
	if(line[i] == '\0')
		return (0);
	return (1);
}

void	is_whitespaces(char **line)
{
	if (!line || !(*line))
		return;
	while (**line && ft_isspace(**line, 0))
		(*line)++;
}

int	ft_skipspace(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && ft_isspace(line[i], 0))
		i++;
	return (i);
}
