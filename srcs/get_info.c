/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulysse <mulysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:14:21 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/25 15:54:44 by mulysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_ep_doubles(t_info *info)
{
	int	i;
	int	p;

	p = 0;
	i = -1;
	while (info->map[++i])
	{
		if (info->map[i] == 'N' || info->map[i] == 'S' || info->map[i] == 'E'
			|| info->map[i] == 'W')
			p++;
		if (info->map[i] == 'B')
			info->box++;
	}
	if (p > 1 || !p)
		return (0);
	return (1);
}

int	get_map(t_info *info)
{
	char	*tmp;
	int		i;

	char *(line) = ft_get_next_line(info->fd);
	if (!line)
		return (ft_printf(2, "Error\nplan empty\n"), 0);
	while (line != NULL)
	{
		i = -1;
		while (line[++i])
			if (!ft_isstrchr("01CBNSEWD \n", line[i]))
				return (free(line), ft_printf(2, "Error\nplan\n"), 0);
		if (line[0] != '\n')
		{
			tmp = ft_strjoin(info->map, line);
			if (!tmp)
				return (free(line), 0);
			free(info->map);
			info->map = tmp;
			free(line);
			info->line++;
		}
		line = ft_get_next_line(info->fd);
	}
	return (1);
}
