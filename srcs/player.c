/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:56:14 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/23 11:26:34 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	knife_animation(t_window *win, t_knife *knife, \
	t_texture *tex, t_all *all)
{
	knife->frame_delay++;
	if (knife->frame_delay >= 2)
	{
		knife->frame_delay = 0;
		if (!knife->normal || knife->aspect)
			knife->animation[knife->i] = (knife->animation[knife->i] + 1) % 37;
		else
			knife->animation[knife->i] = 5 + \
				(knife->animation[knife->i] - 5 + 1) % 3;
		if (all->movement.move[XK_f])
		{
			knife->aspect = true;
			knife->animation[knife->i] = (knife->animation[knife->i] + 1) % 37;
		}
		if (knife->animation[knife->i] % 37 == 0)
			knife->lim++;
		if (knife->lim == 2)
		{
			knife->normal = true;
			knife->lim--;
			knife->aspect = false;
		}
	}
	render_2dsprite(win, &tex->tiles[2][knife->i][knife->animation[knife->i]]);
}

void	update_doors(t_all *all, double dt)
{
	t_obj *(d) = &all->door;
	if (d->status == 1 && all->open_progress < 1.0)
		all->open_progress += dt * 2.0;
	if (all->open_progress > 1.0)
	{
		all->open_progress = 1.0;
		all->door.m->i = 'd';
	}
	d = &all->door;
	if (d->status == 0 && all->open_progress > 0.0)
		all->open_progress -= dt * 2.0;
	if (all->open_progress < 0.0)
	{
		all->open_progress = 0.0;
		all->door.m->i = 'D';
	}
}

static void	try_access_card(t_all *all)
{
	double (dx) = all->player.access.m->x + 0.5 - all->player.x;
	double (dy) = all->player.access.m->y + 0.5 - all->player.y;
	double (dist) = sqrt(dx * dx + dy * dy);
	if (dist < 2)
	{
		all->player.access.status = 1;
		all->player.access.m->i = '0';
	}
}

static void	try_open_door(t_all *all, int status)
{
	double (dx) = all->door.m->x + 0.5 - all->player.x;
	double (dy) = all->door.m->y + 0.5 - all->player.y;
	double (dist) = sqrt(dx * dx + dy * dy);
	if (dist < 2 && dist > 1)
		all->door.status = status;
}

void	player_handling(t_all *all)
{
	knife_animation(&all->window, &all->player.knife, &all->tex, all);
	if (all->movement.move[XK_e])
		try_access_card(all);
	if (all->movement.move[XK_e] && all->player.access.status == 1 \
		&& all->door.status == 0)
		try_open_door(all, 1);
	else if (all->movement.move[XK_e] && all->door.status == 1)
		try_open_door(all, 0);
}
