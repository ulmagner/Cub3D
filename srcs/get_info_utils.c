/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulysse <mulysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:04:17 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/25 16:06:49 by mulysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(char *line, char **path, const char *id)
{
	int (i) = 0;
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

char	**color_split(char *line, char id)
{
	char	**split;

	int (i) = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i++] != id)
		return (printf("????\n"), NULL);
	while (line[i] && ft_isspace(line[i]))
		i++;
	int (j) = i - 1;
	while (line[++j])
		if (!ft_isdigit(line[j]) && line[j] != ',' && !ft_isspace(line[j]))
			return (printf("%c???\n", line[j]), NULL);
	split = ft_split(line + i, ',');
	if (!split || ft_countwords(line + i, ',') != 3)
	{
		if (split)
			ft_tabfree(split);
		return (printf("??\n"), NULL);
	}
	return (split);
}

int	parse_color(char *line, t_color *color, char id)
{
	char **(split) = color_split(line, id);
	if (!split)
		return (0);
	char *(s0) = ft_strtrim(split[0], " \n");
	char *(s1) = ft_strtrim(split[1], " \n");
	char *(s2) = ft_strtrim(split[2], " \n");
	if (!s0 || !s1 || !s2)
	{
		free(s0);
		free(s1);
		return (free(s2), ft_tabfree(split), 0);
	}
	int (r) = ft_atoi(s0);
	int (g) = ft_atoi(s1);
	int (b) = ft_atoi(s2);
	ft_tabfree(split);
	free(s0);
	free(s1);
	free(s2);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	color->r = r;
	color->g = g;
	color->b = b;
	return (1);
}

int	check_duplicates(char *line, t_info *info, t_all *all)
{
	if (!info->npath && parse_texture(line, &info->npath, "NO"))
		info->parsing_nbr++;
	else if (!info->spath && parse_texture(line, &info->spath, "SO"))
		info->parsing_nbr++;
	else if (!info->wpath && parse_texture(line, &info->wpath, "WE"))
		info->parsing_nbr++;
	else if (!info->epath && parse_texture(line, &info->epath, "EA"))
		info->parsing_nbr++;
	else if (!all->df && parse_color(line, &all->floor, 'F'))
	{
		all->df = 1;
		info->parsing_nbr++;
	}
	else if (!all->dc && parse_color(line, &all->ceiling, 'C'))
	{
		all->dc = 1;
		info->parsing_nbr++;
	}
	else
		return (ft_printf(2, "%cError\nWrong information line\n", line[0]), 0);
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
			if (!check_duplicates(line, info, all))
				return (free(line), 0);
		}
		free(line);
		line = ft_get_next_line(info->fd);
	}
	if (line)
		free(line);
	if (info->parsing_nbr != 6)
		return (ft_printf(2, "Error\nToo much info\n"), 0);
	return (1);
}
