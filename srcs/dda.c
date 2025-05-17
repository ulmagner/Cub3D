/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:03:28 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/18 00:34:12 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_playerpos_and_fov(t_player *p, t_raycasting *r, int x, int w)
{
	r->camerax = 2 * x / (double)w - 1;
	r->raydirx = p->dx + p->planex * r->camerax;
	r->raydiry = p->dy + p->planey * r->camerax;
	r->mapx = p->x;
	r->mapy = p->y;
	r->deltadistx = fabs(1 / r->raydirx);
	r->deltadisty = fabs(1 / r->raydiry);
}

void	init_dda(t_raycasting *r, t_player *p)
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

t_map	*dda_function(t_raycasting *r, t_map *tmp)
{
	while (r->hit == 0)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			if (r->stepx > 0)
				tmp = tmp->right;
			else
				tmp = tmp->left;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			if (r->stepy > 0)
				tmp = tmp->down;
			else
				tmp = tmp->up;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (tmp->i == '1' || tmp->i == 'B')
			r->hit = 1;
	}
	return (tmp);
}

void	line_height_calculation(t_all *all, t_raycasting *r, t_player *p)
{
	r->perpwalldist = (r->sidedisty - r->deltadisty);
	if(r->side == 0)
		r->perpwalldist = (r->sidedistx - r->deltadistx);
	r->lineheight = (int)(all->window.main_h / r->perpwalldist);
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
