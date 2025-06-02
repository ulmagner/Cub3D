/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:19:39 by ulmagner          #+#    #+#             */
/*   Updated: 2025/06/02 10:59:29 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	floodfill(t_map *player, t_all *all)
{
	if ((player->up && (player->up->i != '0' && player->up->i != '1'
				&& player->up->i != 'D' && player->up->i != 'B'
				&& player->up->i != 'C' && (player->up->i != 'N'
					&& player->up->i != 'W' && player->up->i != 'E'
					&& player->up->i != 'S')))
		|| (player->down && (player->down->i != '0'
				&& player->down->i != '1' && player->down->i != 'D'
				&& player->down->i != 'B' && player->down->i != 'C'
				&& (player->down->i != 'N' && player->down->i != 'S'
					&& player->down->i != 'W'
					&& player->down->i != 'E')))
		|| (player->left && (player->left->i != '0' && player->left->i != '1'
				&& player->left->i != 'D' && player->left->i != 'B'
				&& player->left->i != 'C' && (player->left->i != 'N'
					&& player->left->i != 'E' && player->left->i != 'W'
					&& player->left->i != 'S')))
		|| ((player->right && player->x < player->right->x)
			&& (player->right->i != '0' && player->right->i != '1'
				&& player->right->i != 'D' && player->right->i != 'B'
				&& player->right->i != 'C' && (player->right->i != 'N'
					&& player->right->i != 'S' && player->right->i != 'E'
					&& player->right->i != 'W')))
		|| (!player->down || !player->up || !player->left
			|| (player->right && player->x > player->right->x)))
		exit(((ft_clearall(all)), EXIT_FAILURE));
}

static void	get_cam(t_map *curr, t_all *all)
{
	if (curr->i == 'E')
	{
		all->player.dx = -1;
		all->player.dy = 0;
	}
	if (curr->i == 'W')
	{
		all->player.dx = 1;
		all->player.dy = 0;
	}
	if (curr->i == 'N')
	{
		all->player.dx = 0;
		all->player.dy = -1;
	}
	if (curr->i == 'S')
	{
		all->player.dx = 0;
		all->player.dy = 1;
	}
	all->player.planex = -all->player.dy * 0.66;
	all->player.planey = all->player.dx * 0.66;
}

void	check_close_map(t_map **map, t_all *all)
{
	t_map	*col;

	t_map *(row) = *map;
	int (l) = 0;
	while (row)
	{
		col = row;
		while (col)
		{
			if (col->i == '0' || col->i == 'D'
				|| col->i == 'C' || col->i == 'B')
				floodfill(col, all);
			if (col->i == 'N' || col->i == 'S'
				|| col->i == 'W' || col->i == 'E')
				get_cam(col, all);
			if (col->x == all->info.column[l] - 1)
				break ;
			col = col->right;
		}
		if (l == all->info.line - 1)
			break ;
		l++;
		row = row->down;
	}
}
