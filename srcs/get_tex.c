/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:43:42 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/23 11:33:21 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_floor(char *line, t_texture *tex)
{
	if (ft_strnstr(line, "floor", ft_strlen(line)))
	{
		if (ft_strnstr(line, "white", ft_strlen(line)))
			tex->nbr_a[0]++;
		if (ft_strnstr(line, "green", ft_strlen(line)))
			tex->nbr_a[1]++;
		if (line[0] == '-' || line[0] == '.')
			tex->nbr_i[0]++;
	}
}

void	check_card(char *line, t_texture *tex)
{
	if (ft_strnstr(line, "card", ft_strlen(line)))
	{
		if (ft_strnstr(line, "card", ft_strlen(line)))
			tex->nbr_a[2]++;
		if (line[0] == '-' || line[0] == '.')
			tex->nbr_i[1]++;
	}
}

void	check_knife(char *line, t_texture *tex)
{
	if (ft_strnstr(line, "knife", ft_strlen(line)))
	{
		tex->nbr_a[3]++;
		if (line[0] == '-' || line[0] == '.')
			tex->nbr_i[2]++;
	}
}

void	check_decor(char *line, t_texture *tex)
{
	if (ft_strnstr(line, "decor", ft_strlen(line)))
	{
		if (ft_strnstr(line, "barrel", ft_strlen(line)))
			tex->nbr_a[4]++;
		if (line[0] == '-' || line[0] == '.')
			tex->nbr_i[3]++;
	}
}
