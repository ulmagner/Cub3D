/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:54:39 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/15 15:04:42 by ulmagner         ###   ########.fr       */
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

static void	direction(t_player *player, double dirx, double diry, int key)
{
	(void) key;
	int	(x) = 0;
	int	(y) = 0;
	double (new_x) = player->x + dirx * player->ms;
	double (new_y) = player->y + diry * player->ms;
	double (old_x) = player->x;
	double (old_y) = player->y;
	char (tmp);
	if (diry < 0 && new_y < player->h->y && player->h->up->i == '1')
			new_y = old_y;
	else if (diry > 0 && new_y > player->h->y + 0.9 && player->h->down->i == '1')
			new_y = old_y;
	if (dirx < 0 && new_x < player->h->x && player->h->left->i == '1')
			new_x = old_x;
	else if (dirx > 0 && new_x > player->h->x + 0.9 && player->h->right->i == '1')
			new_x = old_x;
	player->y = new_y;
	player->x = new_x;
	if (player->y < player->h->y && player->h->i != '1' && ((diry < 0 && key == 2) || (diry < 0 && key == 1) || (diry < 0 && key == 3) || (diry < 0 && key == 4)))
	{
		tmp = player->h->i;
		player->h->i = player->h->up->i;
		player->h->up->i = tmp;
		y = 1;
	}
	else if (player->y > player->h->y + 0.99 && player->h->i != '1' && ((diry > 0 && key == 1) || (diry > 0 && key == 2) || (diry > 0 && key == 3) || (diry > 0 && key == 4)))
	{
		tmp = player->h->i;
		player->h->i = player->h->down->i;
		player->h->down->i = tmp;
		y = 2;
	}
	if (player->x < player->h->x && player->h->i != '1' && ((dirx < 0 && key == 3) || (dirx < 0 && key == 4) || (dirx < 0 && key == 2) || (dirx < 0 && key == 1)))
	{
		tmp = player->h->i;
		player->h->i = player->h->left->i;
		player->h->left->i = tmp;
		x = 1;
	}
	else if (player->x > player->h->x + 0.99 && player->h->i != '1' && ((dirx > 0 && key == 3) || (dirx > 0 && key == 4) || (dirx > 0 && key == 1) || (dirx > 0 && key == 2)))
	{
		tmp = player->h->i;
		player->h->i = player->h->right->i;
		player->h->right->i = tmp;
		x = 2;
	}
	if (x == 1)
	{
		player->h = player->h->left;
	}
	else if (x == 2)
	{
		player->h = player->h->right;
		player->x = player->h->x + 0.01;
	}
	else if (y == 1)
	{
		player->h = player->h->up;
	}
	else if (y == 2)
	{
		player->h = player->h->down;
		player->y = player->h->y + 0.01;
	}
}

int	movement_handling(t_all *all)
{
	t_player *(p) = &all->player;
	if (all->movement.move[XK_w])
		direction(p, p->dx, p->dy, 1);
	else if (all->movement.move[XK_s])
		direction(p, -p->dx, -p->dy, 2);
	if (all->movement.move[XK_a])
		direction(&all->player, -p->planex, -p->planey, 3);
	else if (all->movement.move[XK_d])
		direction(&all->player, p->planex, p->planey, 4);
	if (all->movement.move[XK_e])
		exit((ft_clearall(all), EXIT_FAILURE));
	return (1);
}
