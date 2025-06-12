/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:04:17 by ulmagner          #+#    #+#             */
/*   Updated: 2025/06/12 12:49:48 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(t_info *info, char **path, const char *id)
{
	int (i) = 0;
	while (info->gnl[i] && ft_isspace(info->gnl[i]))
		i++;
	if (ft_strncmp(&info->gnl[i], id, ft_strlen(id)) != 0)
		return (0);
	i += ft_strlen(id);
	while (info->gnl[i] && ft_isspace(info->gnl[i]))
		i++;
	*path = ft_strdup(&info->gnl[i]);
	if (!*path)
		return (0);
	return (1);
}

char	**color_split(t_info *info, char id)
{
	char	**split;

	int (i) = 0;
	while (info->gnl[i] && ft_isspace(info->gnl[i]))
		i++;
	if (info->gnl[i++] != id)
		return (printf("????\n"), NULL);
	while (info->gnl[i] && ft_isspace(info->gnl[i]))
		i++;
	int (j) = i - 1;
	while (info->gnl[++j])
		if (!ft_isdigit(info->gnl[j]) && info->gnl[j] != ','
			&& !ft_isspace(info->gnl[j]))
			return (printf("%c???\n", info->gnl[j]), NULL);
	split = ft_split(info->gnl + i, ',');
	if (!split || ft_countwords(info->gnl + i, ',') != 3)
	{
		if (split)
			ft_tabfree(split);
		return (printf("??\n"), NULL);
	}
	return (split);
}

int	parse_color(t_info *info, t_color *color, char id)
{
	char **(split) = color_split(info, id);
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

int	check_duplicates(t_info *info, t_all *all)
{
	if (!info->npath && parse_texture(info, &info->npath, "NO"))
		info->parsing_nbr++;
	else if (!info->spath && parse_texture(info, &info->spath, "SO"))
		info->parsing_nbr++;
	else if (!info->wpath && parse_texture(info, &info->wpath, "WE"))
		info->parsing_nbr++;
	else if (!info->epath && parse_texture(info, &info->epath, "EA"))
		info->parsing_nbr++;
	else if (!all->df && parse_color(info, &all->floor, 'F'))
	{
		all->df = 1;
		info->parsing_nbr++;
	}
	else if (!all->dc && parse_color(info, &all->ceiling, 'C'))
	{
		all->dc = 1;
		info->parsing_nbr++;
	}
	else
		return (ft_printf(2, "%cError\nWrong information info->gnl\n",
				info->gnl[0]), 0);
	return (1);
}

int	get_tex_mandatory(t_all *all, t_info *info)
{
	info->gnl = ft_get_next_line(info->fd);
	if (!info->gnl)
		return (ft_printf(2, "Error\nplan empty\n"), 0);
	while (info->gnl != NULL)
	{
		if (info->parsing_nbr == 6)
			break ;
		if (info->gnl[0] != '\n')
		{
			if (!check_duplicates(info, all))
				return (0);
		}
		free(info->gnl);
		info->gnl = ft_get_next_line(info->fd);
	}
	if (info->parsing_nbr != 6)
		return (ft_printf(2, "Error\nToo much info\n"), 0);
	return (1);
}
