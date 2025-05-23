/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:14:21 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/23 10:56:30 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_ep_doubles(t_info *info)
{
	int	i;
	int	p;

	p = 0;
	i = -1;
	while (info->map[++i])
	{
		if (info->map[i] == 'N' || info->map[i] == 'S' || info->map[i] == 'E' \
			|| info->map[i] == 'W')
			p++;
		if (info->map[i] == 'B')
			info->box++;
	}
	if (p > 1 || !p)
		return (0);
	return (1);
}

int	parse_texture(char *line, char **path, const char *id)
{
	int	i = 0;

	while (line[i] && ft_isspace(line[i]))
		i++;
	if (ft_strncmp(&line[i], id, ft_strlen(id)) != 0)
		return (0);
	i += ft_strlen(id);
	while (line[i] && ft_isspace(line[i]))
		i++;
	*path = ft_strdup(&line[i]);
	if (!*path)
		return (0);
	return (1);
}

int	parse_color(char *line, t_color *color, char id)
{
	char	**split;
	int		i = 0;

	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] != id)
		return (0);
	split = ft_split(line + i + 1, ',');
	if (!split || ft_countwords(line + i + 1, ',') != 3)
		return (0);
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	ft_tabfree(split);
	return (1);
}

int	get_tex_mandatory(t_all *all, t_info *info)
{
	char *(line) = ft_get_next_line(info->fd);
	if (!line)
		return (ft_printf(2, "Error\nplan empty\n"), 0);
	while (line != NULL)
	{
		if (info->parsing_nbr == 6)
			break ;
		if (line[0] != '\n')
		{
			if (parse_texture(line, &info->npath, "NO") \
				|| parse_texture(line, &info->spath, "SO") \
				|| parse_texture(line, &info->wpath, "WE") \
				|| parse_texture(line, &info->epath, "EA") \
				|| parse_color(line, &all->floor, 'F') \
				|| parse_color(line, &all->ceiling, 'C'))
				info->parsing_nbr++;
			else
			{
				free(line);
				return (ft_printf(2, "Error\nWrong information line\n", 0));
			}
		}
		free(line);
		line = ft_get_next_line(info->fd);
	}
	if (info->parsing_nbr != 6)
		return (ft_printf(2, "Error\nToo much info\n"), 0);
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
	if (!check_ep_doubles(info))
		return (ft_printf(2, "Error\nplanS\n"), 0);
	printf("%s\n", info->map);
	return (1);
}
