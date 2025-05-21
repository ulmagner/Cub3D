/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:19:39 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/21 21:44:43 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	floodfill(t_map *player, t_all *all, int l)
// {
// 	if (((player->x == 0 || player->x == all->info.column[l])
// 			&& player->i != '1')
// 		|| ((player->y == 0 || player->y == all->info.line)
// 			&& player->i != '1'))
// 		exit(((ft_clearall(all)), EXIT_FAILURE));
// 	player->is_visited = 1;
// 	if (player->right->i != '1' 
// 		&& player->right != NULL && !player->right->is_visited)
// 		floodfill(player->right, all, l);
// 	if (player->left->i != '1' 
// 		&& player->left != NULL && !player->left->is_visited)
// 		floodfill(player->left, all, l);
// 	if (player->up->i != '1' 
// 		&& player->up != NULL && !player->up->is_visited)
// 		floodfill(player->up, all, l);
// 	if (player->down->i != '1' 
// 		&& player->down != NULL && !player->down->is_visited)
// 		floodfill(player->down, all, l);
// }

static void	start_floodfill(t_map *curr, t_all *all, int l)
{
	// t_map *(p) = curr;
	// floodfill(p, all, l);
	(void) l;
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

int	check_close_map(t_map **map, t_all *all)
{
	t_map	*curr;

	curr = *map;
	int (l) = 0;
	while (curr)
	{
		if (curr->x == all->info.column[l] - 1)
			l++;
		if (curr->i == 'E' || curr->i == 'W' 
			|| curr->i == 'S' || curr->i == 'N')
		{
			start_floodfill(curr, all, l);
			break ;
		}
		curr = curr->right;
	}
	return (1);
}
