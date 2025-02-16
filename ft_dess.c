/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dess.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bimane <bimane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:59:08 by bimane            #+#    #+#             */
/*   Updated: 2025/01/29 09:06:33 by bimane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_designe(int pst)
{
    int couleur;
    
    if(pst == '0')
        couleur = 0x042f66;
    else if (pst == '1')
        couleur = 0x3fb2d1;
    else if (pst == '2')
        couleur = 0xffe8be;
    else
        couleur = 0;

    return(couleur);
}

// void ft_put_pixel()
// {
    
// }