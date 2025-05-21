/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:03:28 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/21 17:50:22 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_playerpos_and_fov(t_player *p, t_raycasting *r, int w)
{
	r->camerax = 2 * r->x / (double)w - 1;
	r->raydirx = p->dx + p->planex * r->camerax;
	r->raydiry = p->dy + p->planey * r->camerax;
	r->mapx = p->x;
	r->mapy = p->y;
	r->deltadistx = fabs(1 / r->raydirx);
	r->deltadisty = fabs(1 / r->raydiry);
}

static void	init_dda(t_raycasting *r, t_player *p)
{
	if (r->raydirx < 0)
	{
		r->stepx = -1;
		r->sidedistx = (p->x - r->mapx) * r->deltadistx;
	}
	else
	{
		r->stepx = 1;
		r->sidedistx = (r->mapx + 1.0 - p->x) * r->deltadistx;
	}
	if (r->raydiry < 0)
	{
		r->stepy = -1;
		r->sidedisty = (p->y - r->mapy) * r->deltadisty;
	}
	else
	{
		r->stepy = 1;
		r->sidedisty = (r->mapy + 1.0 - p->y) * r->deltadisty;
	}
}

static void	line_height_calculation(t_all *all, t_raycasting *r, t_player *p)
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

static t_map	*dda_function(t_raycasting *r, t_map *tmp, char c, t_all *all)
{
	while (!r->hit && tmp)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			if (r->stepx > 0)
				tmp = tmp->right;
			else
				tmp = tmp->left;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			if (r->stepy > 0)
				tmp = tmp->down;
			else
				tmp = tmp->up;
			r->side = 1;
		}
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
				rendering_image(&all->tex.tiles[1][0][0], all, r->x, 0.5);
			}
		}
	}
	return (tmp);
}

void	raycasting(t_all *all, t_player *p, t_raycasting *r)
{
	int (w) = all->window.main_w;
	t_map *(cp) = p->h;
	while (r->x < w)
	{
		cp = p->h;
		r->hit = false;
		set_playerpos_and_fov(p, r, w);
		init_dda(r, p);
		cp = dda_function(r, cp, '1', all);
		line_height_calculation(all, r, p);
		all->zbuffer[r->x] = r->perpwalldist;
		if (cp->i == '1')
			rendering_image(&all->tex.tiles[1][0][0], all, r->x, 1);
		if (cp->i == 'D' && all->open_progress < 1.0)
		{
			r->perpwalldist -= all->open_progress;
			if (r->perpwalldist < 0)
				r->perpwalldist = 0;
			rendering_image(&all->tex.tiles[1][0][0], all, r->x, 0.5);
		}
		// else if (cp->i == 'd' && all->open_progress < 1.0)
		// {
		// 	r->perpwalldist += all->open_progress;
		// 	if (r->perpwalldist >1)
		// 		r->perpwalldist = 1;
		// 	rendering_image(&all->tex.tiles[1][0][0], all, r->x, 0.5);
		// }
		r->y = r->drawend + 1;
		while (r->y < all->window.main_h)
			floor_ceiling_raycasting(all, r, cp, p);
		r->x++;
	}
}
