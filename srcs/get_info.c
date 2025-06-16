/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:14:21 by ulmagner          #+#    #+#             */
/*   Updated: 2025/06/16 09:59:56 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_ep_doubles(t_info *info)
{
	int	i;
	int	p;
	int	c;
	int	d;

	p = 0;
	c = 0;
	d = 0;
	i = -1;
	while (info->map[++i])
	{
		if (info->map[i] == 'N' || info->map[i] == 'S' || info->map[i] == 'E'
			|| info->map[i] == 'W')
			p++;
		if (info->map[i] == 'C')
			c++;
		if (info->map[i] == 'D')
			d++;
		if (info->map[i] == 'B')
			info->box++;
	}
	if (p > 1 || !p || !c || !d || c > 1 || d > 1)
		return (0);
	return (1);
}

int	get_map(t_info *info)
{
	char *(tmp) = NULL;
	int (i) = -1;
	while (info->gnl != NULL)
	{
		i = -1;
		while (info->gnl[++i])
			if (!ft_isstrchr("01CBNSEWD \n", info->gnl[i]))
				return (ft_printf(2, "Error\nplan\n"), 0);
		if (info->gnl[0] != '\n')
		{
			tmp = ft_strjoin(info->map, info->gnl);
			if (!tmp)
				return (0);
			free(info->map);
			info->map = tmp;
			info->line++;
		}
		free(info->gnl);
		info->gnl = ft_get_next_line(info->fd);
	}
	return (1);
}
