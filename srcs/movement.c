/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:54:39 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/20 18:58:47 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	walk(t_player *player, double dirx, double diry)
{
	double (old_x) = player->x;
	double (old_y) = player->y;
	double (new_x) = old_x + dirx * player->ms;
	double (new_y) = old_y + diry * player->ms;
	if (dirx > 0 && player->h->right && (player->h->right->i == '1' \
		|| player->h->right->i == 'B' || player->h->right->i == 'D' \
		|| player->h->right->i == 'C') && new_x >= player->h->x + 1)
		new_x = old_x;
	else if (dirx < 0 && player->h->left && (player->h->left->i == '1' \
		|| player->h->left->i == 'B' || player->h->left->i == 'D' \
		|| player->h->left->i == 'C') && new_x <= player->h->x)
		new_x = old_x;
	player->x = new_x;
	new_y = old_y + diry * player->ms;
	if (diry > 0 && player->h->down && (player->h->down->i == '1' || \
		player->h->down->i == 'B' || player->h->down->i == 'D' || \
		player->h->down->i == 'C') && new_y >= player->h->y + 1)
		new_y = old_y;
	else if (diry < 0 && player->h->up && (player->h->up->i == '1' \
		|| player->h->up->i == 'B' || player->h->up->i == 'D' \
		|| player->h->up->i == 'C') && new_y <= player->h->y)
		new_y = old_y;
	player->y = new_y;
}

static t_map	*check_height_cases(t_player *player, \
	int new_tile_x, int new_tile_y)
{
	t_map *(new_tile) = NULL;
	if (new_tile_y < player->h->y)
		new_tile = player->h->up;
	else if (new_tile_y > player->h->y)
		new_tile = player->h->down;
	if (new_tile_y == player->h->y)
	{
		if (new_tile_x < player->h->x)
			new_tile = player->h->left;
		else if (new_tile_x > player->h->x)
			new_tile = player->h->right;
	}
	else if (new_tile_y != player->h->y && new_tile_x != player->h->x)
	{
		if (new_tile_y < player->h->y && new_tile_x < player->h->x)
			new_tile = player->h->up->left;
		else if (new_tile_y < player->h->y && new_tile_x > player->h->x)
			new_tile = player->h->up->right;
		else if (new_tile_y > player->h->y && new_tile_x < player->h->x)
			new_tile = player->h->down->left;
		else if (new_tile_y > player->h->y && new_tile_x > player->h->x)
			new_tile = player->h->down->right;
	}
	return (new_tile);
}

static void	direction(t_player *player, double dirx, double diry)
{
	t_map	*new_tile;
	char	new_tile_i;

	new_tile = NULL;
	walk(player, dirx, diry);
	int (new_tile_x) = (int)player->x;
	int (new_tile_y) = (int)player->y;
	if (new_tile_x != (int)player->h->x || new_tile_y != (int)player->h->y)
	{
		new_tile = check_height_cases(player, new_tile_x, new_tile_y);
		if (new_tile && (new_tile->i != '1' && new_tile->i != 'B' \
			&& new_tile->i != 'D' && new_tile->i != 'C'))
		{
			new_tile_i = player->h->i;
			player->h->i = new_tile->i;
			new_tile->i = new_tile_i;
			player->h = new_tile;
		}
	}
}

int	movement_handling(t_all *all)
{
	t_player *(p) = &all->player;
	if (all->movement.move[XK_w])
		direction(p, p->dx, p->dy);
	else if (all->movement.move[XK_s])
		direction(p, -p->dx, -p->dy);
	if (all->movement.move[XK_a])
		direction(&all->player, -p->planex, -p->planey);
	else if (all->movement.move[XK_d])
		direction(&all->player, p->planex, p->planey);
	return (1);
}
