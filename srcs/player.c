/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:56:14 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/20 18:21:33 by ulmagner         ###   ########.fr       */
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
	render_2dsprite(win, &tex->tiles[3][knife->i][knife->animation[knife->i]]);
}

static bool	get_access_card(t_player *player)
{
	if (player->h->right->i == 'C')
		return (true);
	else if (player->h->left->i == 'C')
		return (true);
	if (player->h->down->i == 'C')
		return (true);
	else if (player->h->up->i == 'C')
		return (true);
	return (false);
}

void	update_doors(t_all *all, double dt)
{
	t_obj *(d) = &all->door;
	if (d->status == 1 && all->open_progress < 1.0)
		all->open_progress += dt * 2.0;
	if (all->open_progress > 1.0)
	{
		all->open_progress = 1.0;
		all->door.m->i = '0';
	}
}

static void	try_open_door(t_all *all)
{
	double (dx) = all->door.m->x + 0.5 - all->player.x;
	double (dy) = all->door.m->y + 0.5 - all->player.y;
	double (dist) = sqrt(dx * dx + dy * dy);
	if (dist < 4)
		all->door.status = 1;
}

void	player_handling(t_all *all)
{
	knife_animation(&all->window, &all->player.knife, &all->tex, all);
	if (get_access_card(&all->player) && all->movement.move[XK_e])
		all->player.access.status = 1;
	if (all->movement.move[XK_space] && all->player.access.status == 1)
		try_open_door(all);
}
