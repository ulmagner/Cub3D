/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:54:39 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/13 13:58:56 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	movement_p(int keycode, t_all *all)
{
	all->movement.move[keycode] = true;
	if (keycode == XK_Escape)
		exit((ft_clearall(all), EXIT_SUCCESS));
	return (0);
}

int	movement_r(int keycode, t_all *all)
{
	all->movement.move[keycode] = false;
	// check_mouvment(&all->player);
	return (0);
}

static void	direction(t_player *player, double dirx, double diry)
{
	double (new_x) = player->x + dirx * player->ms;
	double (new_y) = player->y + diry * player->ms;
	double (old_x) = player->x;
	double (old_y) = player->y;
	if (diry < 0 && new_y < player->h->y && player->h->up->i == '1')
			new_y = old_y;
	if (diry > 0 && new_y > player->h->y + 0.9 && player->h->down->i == '1')
			new_y = old_y;
	if (dirx < 0 && new_x < player->h->x && player->h->left->i == '1')
			new_x = old_x;
	if (dirx > 0 && new_x > player->h->x + 0.9 && player->h->right->i == '1')
			new_x = old_x;
	player->x = new_x;
	player->y = new_y;
	if (player->y < player->h->y && player->h->i != '1')
		player->h = player->h->up;
	else if (player->y > player->h->y + 0.9 && player->h->i != '1')
		player->h = player->h->down;
	if (player->x < player->h->x && player->h->i != '1')
		player->h = player->h->left;
	else if (player->x > player->h->x + 0.9 && player->h->i != '1')
		player->h = player->h->right;
}

int	movement_handling(t_all *all)
{
	t_player *(p) = &all->player;
	if (all->movement.move[XK_w])
		direction(p, p->dx, p->dy);
	if (all->movement.move[XK_s])
		direction(p, -p->dx, -p->dy);
	if (all->movement.move[XK_a])
		direction(&all->player, p->dx, -p->dy);
	if (all->movement.move[XK_d])
		direction(&all->player, -p->dx, p->dy);
	if (all->movement.move[XK_e])
		exit((ft_clearall(all), EXIT_FAILURE));
	return (1);
}
