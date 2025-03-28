/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <magneronulysse@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:14:21 by ulmagner          #+#    #+#             */
/*   Updated: 2025/03/28 18:20:45 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	empty_string(t_info *info)
{
	info->map = malloc(1);
	if (!info->map)
		return (0);
	info->map[0] = '\0';
	return (1);
}

static int	check_ep_doubles(t_info *info)
{
	int	i;
	int	e;
	int	p;

	e = 0;
	p = 0;
	i = -1;
	while (info->map[++i])
	{
		if (info->map[i] == 'E')
			e++;
		if (info->map[i] == 'P')
			p++;
		/*
		if (info->map[i] == 'C')
			info->coin++;
		if (info->map[i] == 'F')
			info->trap++;
		if (info->map[i] == 'O')
			info->oeil++;*/
	}
	if (e > 1 || !e || p > 1 || !p)
		return (0);
	return (1);
}

int	get_map(t_info *info, int *l, int *c)
{
	char	*tmp;
	int		i;

	char *(line) = ft_get_next_line(info->fd);
	if (!line)
		return (ft_printf(2, "Error\nplan empty\n"), 0);
	*c = ft_strlen(line) - 1;
	while (line != NULL)
	{
		i = -1;
		while (line[++i])
			if (!ft_isstrchr("01CEPOF\n", line[i]))
				return (free(line), ft_printf(2, "Error\nplan\n"), 0);
		tmp = ft_strjoin(info->map, line);
		if (!tmp)
			return (free(line), 0);
		free(info->map);
		info->map = tmp;
		free(line);
		(*l)++;
		line = ft_get_next_line(info->fd);
	}
	if (!check_ep_doubles(info))
		return (ft_printf(2, "Error\nplan\n"), 0);
	return (1);
}

