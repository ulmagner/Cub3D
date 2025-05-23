/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:41:51 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/23 11:29:36 by ulmagner         ###   ########.fr       */
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

static int	parse_file(char **line, t_texture *tex, char **path)
{
	char	*tmp;

	check_floor(*line, tex);
	check_card(*line, tex);
	check_knife(*line, tex);
	check_decor(*line, tex);
	if (*line[0] == '.')
		tex->nbr_image++;
	tmp = ft_strjoin(*path, *line + 1);
	if (!tmp)
		return (free(*line), 0);
	free(*path);
	*path = tmp;
	free(*line);
	return (1);
}

static int	init_i(t_texture *tex)
{
	tex->nbr_image = 0;
	tex->nbr_i = ft_calloc(6, sizeof(int));
	if (!tex->nbr_i)
		return (0);
	tex->nbr_a = ft_calloc(6, sizeof(int));
	if (!tex->nbr_a)
		return (free(tex->nbr_i), 0);
	return (tex->nbr_i && tex->nbr_a);
}

int	get_paths(char *file, t_texture *tex)
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
	int (q) = -1;
	while (line[++q] != '.')
		;
	line = ft_strdup(line + q);
	if (!line)
		return (0);
	printf("%s\n", line);
	while (line)
	{
		if (!parse_file(&line, tex, &path))
			return (free(line), close(fd), free(path), 0);
		nbr_line++;
		line = ft_get_next_line(fd);
	}
	if (nbr_line != 42)
		return (close(fd), free(path), free(line), 0);
	tex->path_texture = ft_split(path, '\n');
	if (!tex->path_texture)
		return (close(fd), free(path), free(line), 0);
	return (free(path), close(fd), 1);
}
