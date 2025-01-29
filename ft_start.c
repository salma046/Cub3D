/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:27:02 by bimane            #+#    #+#             */
/*   Updated: 2025/01/29 09:51:02 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_mini_map(t_jeux *jeux)
{
    int i;
    int j;
    int i_de;
    int j_de;
    int desgn;

    i = 0;
    i_de = jeux->cube.map_heigh;
    j_de = jeux->cube.map_width;
    
    if((i_de * j_de) >= 2000 )
        return(1);
    while(i < i_de)
    {
        j = 0;
        while(j < j_de)
        {
            desgn = ft_designe(jeux->cube.cub_map[i][j]);
            if(desgn)
                ft_put_pexel();
            j++;
        }
        i++;
    }
    ft_joueur();
    
}


int ft_start(t_jeux *jeux)
{
    int i;
    i = 0;
    /*-->premiere vue a faire cest le raycasting*/
    while(i < 1024)
    {
        /*-->lancement des rayons
        **-->dda de rayon roncontre les murs
        **-->affichage des murs
        */
       i++;
    }
    ft_mini_map(jeux);

    
}