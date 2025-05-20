/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:19:39 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/20 15:55:46 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	floodfill(t_map *player, t_all *all)
{
	if (((player->x == 0 || player->x == all->info.column - 1)
			&& player->i != '1')
		|| ((player->y == 0 || player->y == all->info.line - 1)
			&& player->i != '1'))
		exit(((ft_clearall(all)), EXIT_FAILURE));
	player->is_visited = 1;
	if (player->right->i != '1' \
		&& player->right != NULL && !player->right->is_visited)
		floodfill(player->right, all);
	if (player->left->i != '1' \
		&& player->left != NULL && !player->left->is_visited)
		floodfill(player->left, all);
	if (player->up->i != '1' \
		&& player->up != NULL && !player->up->is_visited)
		floodfill(player->up, all);
	if (player->down->i != '1' \
		&& player->down != NULL && !player->down->is_visited)
		floodfill(player->down, all);
}

static int	start_floodfill(t_map *curr, t_all *all)
{
	t_map	*p;

	if (curr->i == 'E' || curr->i == 'W' || curr->i == 'S' || curr->i == 'N')
	{
		p = curr;
		floodfill(p, all);
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
		return (1);
	}
	return (0);
}

int	check_close_map(t_map **map, t_all *all)
{
	t_map	*curr;

	curr = *map;
	while (curr)
	{
		if (start_floodfill(curr, all))
			break ;
		curr = curr->right;
	}
	return (1);
}
