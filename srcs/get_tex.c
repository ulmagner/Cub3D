/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:43:42 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/10 00:57:39 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_wall(char *line, t_texture *tex)
{
	if (ft_strnstr(line, "wall", ft_strlen(line)))
	{
		if (ft_strnstr(line, "N", ft_strlen(line)))
			tex->nbr_a[0]++;
		// else if (ft_strnstr(line, "bas", ft_strlen(line)))
		// 	tex->nbr_a[1]++;
		// else if (ft_strnstr(line, "gauche", ft_strlen(line)))
		// 	tex->nbr_a[2]++;
		// else if (ft_strnstr(line, "droite", ft_strlen(line)))
		// 	tex->nbr_a[3]++;
		// else if (ft_strnstr(line, "corner", ft_strlen(line)))
		// 	tex->nbr_a[4]++;
		if (line[0] == '-' || line[0] == '.')
			tex->nbr_i[0]++;
	}
}

void	check_floor(char *line, t_texture *tex)
{
	if (ft_strnstr(line, "floor", ft_strlen(line)))
	{
		tex->nbr_a[1]++;
		if (line[0] == '-' || line[0] == '.')
			tex->nbr_i[1]++;
	}
}
