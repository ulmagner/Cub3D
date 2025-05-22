/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:41:51 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/22 19:20:54 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*empty_stringe(char *path)
{
	path = malloc(1);
	if (!path)
		return (NULL);
	path[0] = '\0';
	return (path);
}

static int	parse_file(char **line, t_texture *tex, char **path, t_all *all)
{
	char	*tmp;
	char	*str;

	check_wall(*line, tex, all);
	check_floor(*line, tex);
	check_card(*line, tex);
	check_knife(*line, tex);
	check_decor(*line, tex);
	if (tex->nbr_a[0] && !tex->nbr_a[1])
		str = ft_strdup(all->info.npath);
	else if (tex->nbr_a[1] && !tex->nbr_a[2])
		str = ft_strdup(all->info.spath);
	else if (tex->nbr_a[2] && !tex->nbr_a[3])
		str = ft_strdup(all->info.wpath);
	else if (tex->nbr_a[3] && all->w)
	{
		str = ft_strdup(all->info.epath);
		all->w = 0;
	}
	else
		str = ft_strdup(*line + 1);
	if (!str)
		return (0);
	if (*line[0] == '.')
		tex->nbr_image++;
	tmp = ft_strjoin(*path, str);
	free(str);
	if (!tmp)
		return (free(str), 0);
	free(*path);
	*path = tmp;
	// free(*line);
	return (1);
}

static int	init_i(t_texture *tex)
{
	tex->nbr_image = 0;
	tex->nbr_i = ft_calloc(6, sizeof(int));
	if (!tex->nbr_i)
		return (0);
	tex->nbr_a = ft_calloc(10, sizeof(int));
	if (!tex->nbr_a)
		return (free(tex->nbr_i), 0);
	return (tex->nbr_i && tex->nbr_a);
}

int	get_paths(char *file, t_texture *tex, t_all *all)
{
	char *(path) = empty_stringe(NULL);
	int (nbr_line) = 0;
	if (!path || !init_i(tex))
		return (free(path), 0);
	int (fd) = open(file, O_RDONLY);
	if (fd == -1)
		return (free(path), 0);
	char *(line) = ft_get_next_line(fd);
	if (!line)
		return (close(fd), free(path), 0);
	all->w = 0;
	int (q) = -1;
	while (line[++q] != '.')
		;
	line = line + q;
	while (line)
	{
		if (!parse_file(&line, tex, &path, all))
			return (free(line), close(fd), free(path), 0);
		nbr_line++;
		line = ft_get_next_line(fd);
	}
	if (nbr_line != 46)
		return (close(fd), free(path), free(line), 0);
	tex->path_texture = ft_split(path, '\n');
	if (!tex->path_texture)
		return (close(fd), free(path), free(line), 0);
	return (free(path), close(fd), 1);
}
