/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulysse <mulysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:41:54 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/25 12:49:28 by mulysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	hit(t_map *tmp, t_raycasting *r, t_all *all, char c)
{
	if (tmp && (tmp->i == c || tmp->i == 'D'))
		r->hit = true;
	else if (tmp->i == 'd')
	{
		line_height_calculation(all, r, &all->player);
		if (all->open_progress > 0.0)
		{
			r->perpwalldist += all->open_progress;
			if (r->perpwalldist > 1)
				r->perpwalldist = 1;
			rendering_image(&all->tex.walls[2], all, r->x, 0.6);
		}
	}
}

static void	trim_newline(char *str)
{
	int (len) = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

int	walls_tiles(t_all *all, t_texture *tex)
{
	int (i) = -1;
	tex->walls = malloc(sizeof(t_image) * 4);
	if (!tex->walls)
		return (0);
	trim_newline(all->info.npath);
	trim_newline(all->info.spath);
	trim_newline(all->info.wpath);
	trim_newline(all->info.epath);
	tex->walls[0].img_path = all->info.npath;
	tex->walls[1].img_path = all->info.spath;
	tex->walls[2].img_path = all->info.wpath;
	tex->walls[3].img_path = all->info.epath;
	while (++i < 4)
	{
		if (!create_image(&tex->walls[i], &all->window))
			return (0);
	}
	return (1);
}

void	line_height_calculation(t_all *all, t_raycasting *r, t_player *p)
{
	r->perpwalldist = (r->sidedisty - r->deltadisty);
	if (r->side == 0)
		r->perpwalldist = (r->sidedistx - r->deltadistx);
	double (corrected_dist) = fmax(r->perpwalldist, 1);
	r->lineheight = (int)(all->window.main_h / corrected_dist);
	r->drawstart = -r->lineheight / 2 + all->window.main_h / 2;
	if (r->drawstart < 0)
		r->drawstart = 0;
	r->drawend = r->lineheight / 2 + all->window.main_h / 2;
	if (r->drawend >= all->window.main_h)
		r->drawend = all->window.main_h - 1;
	if (r->side == 0)
		r->tex_x = p->y + r->perpwalldist * r->raydiry;
	else
		r->tex_x = p->x + r->perpwalldist * r->raydirx;
	r->tex_x -= floor(r->tex_x);
}
