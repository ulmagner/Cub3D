/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:54:39 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/13 12:11:32 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int movement_p(int keycode, t_all *all)
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

static void	direction(t_player *player, t_map *next, int dirx, int diry)
{
	if (next->i != '1')
	{
		if (dirx)
		{
			player->x += dirx * player->ms;
			if ((dirx > 0 && player->x >= next->x)
			|| (dirx < 0 && player->x <= next->x))
			{
				printf("player [x:y] [%f %f] case\n", player->x, player->y);
				player->h = next;
			}
		}
		else
		{
			player->y += diry * player->ms;
			if ((diry > 0 && player->y >= next->y)
			|| (diry < 0 && player->y <= next->y))
			{
				printf("player [x:y] [%f %f] case\n", player->x, player->y);
				player->h = next;
			}
		}
	}
}

int	movement_handling(t_all *all)
{
	if (all->movement.move[XK_w])
		direction(&all->player, all->player.h->up, 0, -1);
	if (all->movement.move[XK_s])
		direction(&all->player, all->player.h->down, 0, 1);
	if (all->movement.move[XK_a])
		direction(&all->player, all->player.h->left, -1, 0);
	if (all->movement.move[XK_d])
		direction(&all->player, all->player.h->right, 1, 0);
	if (all->movement.move[XK_e])
	{
		exit((ft_clearall(all), EXIT_FAILURE));
	}
	return (1);
}
