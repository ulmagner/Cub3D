/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:02:29 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/10 16:16:54 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dir_up(t_player *player, t_movement *movement, t_all *all)
{
	if (movement->move[XK_w] && player->h->up->i != '1')
	{
		ft_memset(movement->i_move, 0, sizeof(movement->i_move));
		movement->i_move[0] = true;
		// player->i = 0;
		// if (all->i - all->frameplayer >= (int)(100 / 60))
		// {
		// 	if ((player->animation[0] + 1) % 6 == 0)
		// 		player->animation[0] += 2;
		// 	player->animation[0] = (player->animation[0] + 1) % 6;
		// }
		player->y -= player->ms;
		if (player->y <= player->h->up->y + player->ms)
		{
			printf("[x:y] [%f %f] case\n", all->player.x, all->player.y);
			player->h = player->h->up;
			all->step++;
		}
	}
}

void	dir_down(t_player *player, t_movement *movement, t_all *all)
{
	if (movement->move[XK_s] && player->h->down->i != '1')
	{
		ft_memset(movement->i_move, 0, sizeof(movement->i_move));
		movement->i_move[1] = true;
		// player->i = 1;
		// if (all->i - all->frameplayer >= (int)(100 / 60))
		// {
		// 	if ((player->animation[1] + 1) % 6 == 0)
		// 		player->animation[1] += 2;
		// 	player->animation[1] = (player->animation[1] + 1) % 6;
		// }
		player->y += player->ms;
		if (player->y >= player->h->down->y - player->ms)
		{
			printf("down [x:y] [%f %f] case\n", player->x, player->y);
			player->h = player->h->down;
			all->step++;
		}
	}
}

void	dir_left(t_player *player, t_movement *movement, t_all *all)
{
	if (movement->move[XK_a] && player->h->left->i != '1')
	{
		ft_memset(movement->i_move, 0, sizeof(movement->i_move));
		movement->i_move[2] = true;
		// player->i = 2;
		// if (all->i - all->frameplayer >= (int)(100 / 60))
		// {
		// 	if ((player->animation[2] + 1) % 6 == 0)
		// 		player->animation[2] += 2;
		// 	player->animation[2] = (player->animation[2] + 1) % 6;
		// }
		player->x -= player->ms;
		if (player->x <= player->h->left->x + player->ms)
		{
			printf("left: [x:y] [%f %f] pxl\n", player->x, player->y);
			all->step++;
			player->h = player->h->left;
		}
	}
}

void	dir_right(t_player *player, t_movement *movement, t_all *all)
{
	if (movement->move[XK_d] && player->h->right->i != '1')
	{
		ft_memset(movement->i_move, 0, sizeof(movement->i_move));
		movement->i_move[3] = 1;
		// player->i = 3;
		// if (all->i - all->frameplayer >= (int)(100 / 60))
		// {
		// 	if ((player->animation[3] + 1) % 6 == 0)
		// 		player->animation[3] += 2;
		// 	player->animation[3] = (player->animation[3] + 1) % 6;
		// }
		player->x += player->ms;

		if (player->x >= player->h->right->x - player->ms)
		{
			printf("right [x:y] [%f %f] case\n", player->x, player->y);
			player->h = player->h->right;
			all->step++;
		}
	}
}
