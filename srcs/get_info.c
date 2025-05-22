/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:14:21 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/22 19:23:38 by ulmagner         ###   ########.fr       */
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

int	get_c(char *line, t_color *color, int i)
{
	char			*col;

	int (j) = i;
	int (k) = 0;
	int (count) = 1;
	int (a) = 0;
	bool (is) = false;
	while (line[++j] == ' ')
		;
	if (line[j] < '0' || line[j] > '9')
		return (printf("1\n"), 0);
	j = i - 1;
	while (line[++j])
	{
		k = j;
		is = false;
		while (line[k] && line[k] >= '0' && line[k] <= '9')
		{
			is = true;
			k++;
		}
		if (is)
		{
			if (k - j > 3 || count > 3)
				return (0);
			col = malloc(sizeof(char) * (k - j + 1));
			if (!col)
				return (0);
			a = 0;
			while (line[j] && line[j] >= '0' && line[j] <= '9')
				col[a++] = line[j++];
			j = k;
			col[a] = '\n';
			if (count == 1)
				color->r = ft_atoi(col);
			else if (count == 2)
				color->g = ft_atoi(col);
			else if (count == 3)
				color->b = ft_atoi(col);
			if (color->r > 255 || color->g > 255 || color->b > 255)
				return (0);
			free(col);
		}
		if (line[j] == ',')
			count++;
	}
	printf("%d %d %d\n", color->r, color->g, color->b);
	return (1);
}

int	get_t(char *line, char **tex, int i)
{
	char	*tmp;

	int (j) = i - 1;
	*tex = ft_calloc(1, sizeof(char));
	if (!*tex)
		return (0);
	while (ft_isalpha(line[++j]))
		;
	while (line[++j])
	{
		if (ft_isalpha(line[j]))
			break ;
	}
	if (j == ft_strlen(line))
		return (ft_printf(2, "Error\nWrong informations\n"), 0);
	tmp = ft_strjoin(*tex, line + j);
	if (!tmp)
		return (free(line), 0);
	free(*tex);
	*tex = tmp;
	return (1);
}

int	get_tex_mandatory(t_all *all, t_info *info)
{
	int		i;

	char *(line) = ft_get_next_line(info->fd);
	if (!line)
		return (ft_printf(2, "Error\nplan empty\n"), 0);
	while (line != NULL)
	{
		if (info->parsing_nbr == 6)
			break ;
		if (line[0] != '\n')
		{
			i = -1;
			while (line[++i])
			{
				if (ft_isalpha(line[i]))
					break ;
			}
			if (i == ft_strlen(line))
				return (ft_printf(2, "Error\n1Wrong informations\n"), 0);
			if (line[i] > 'Z')
				return (ft_printf(2, "Error\n2Wrong informations\n"), 0);
			if (line[i] != 'N' && line[i] != 'S' && line[i] != 'E' \
				&& line[i] != 'W' && line[i] != 'F' && line[i] != 'C')
				return (ft_printf(2, "Error\n3Wrong informations\n"), 0);
			if (ft_isalpha(line[i + 1]) && (line[i + 1] != 'O' && \
				line[i + 1] != 'E' && line[i + 1] != 'A' && line[i + 1] != ' '))
				return (ft_printf(2, "Error\n4Wrong informations\n"), 0);
			if (line[i] == 'N')
			{
				if (!get_t(line, &info->npath, i))
					return (0);
				printf("%s\n", info->npath);
			}
			if (line[i] == 'S')
			{
				if (!get_t(line, &info->spath, i))
					return (0);
			}
			if (line[i] == 'W')
			{
				if (!get_t(line, &info->wpath, i))
					return (0);
			}
			if (line[i] == 'E')
			{
				if (!get_t(line, &info->epath, i))
					return (0);
			}
			if (line[i] == 'F')
			{
				if (!get_c(line, &all->floor, i))
					return (0);
			}
			if (line[i] == 'C')
			{
				if (!get_c(line, &all->ceiling, i))
					return (0);
			}
			free(line);
			info->parsing_nbr++;
		}
		line = ft_get_next_line(info->fd);
	}
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
