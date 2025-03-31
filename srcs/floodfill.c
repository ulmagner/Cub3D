/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:19:39 by ulmagner          #+#    #+#             */
/*   Updated: 2025/03/31 11:32:04 by ulmagner         ###   ########.fr       */
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

/*
static void	get_c_p_info(t_map *curr, t_all *all)
{
	if (curr->i == 'C')
	{
		all->slime[all->info.slime].x = curr->x * 64;
		all->slime[all->info.slime].frameslime = 0;
		all->slime[all->info.slime].y = curr->y * 64;
		all->slime[all->info.slime++].r = 11.0;
	}
	if (curr->i == 'F')
	{
		all->trap[all->info.fire].x = curr->x * 64;
		all->trap[all->info.fire].frametrap = 0;
		all->trap[all->info.fire].y = curr->y * 64;
		all->trap[all->info.fire++].r = 64.0;
	}
}*/

static int	start_floodfill(t_map *curr, t_all *all)
{
	//int	i;

	//i = -1;
	if (curr->i == 'E' || curr->i == 'W' || curr->i == 'S' || curr->i == 'N')
	{
		all->player.x = curr->x * 64;
		all->player.y = curr->y * 64;
		//all->player.r = 31.0;
		floodfill(curr, all);
	}
	if (curr->i == 'E')
	{
		all->player.dx = -1;
		all->player.dy = 0;
		all->player.planex = 0;
		all->player.planey = 0.66;
	}
	if (curr->i == 'W')
	{
		all->player.dx = 1;
		all->player.dy = 0;
		all->player.planex = 0;
		all->player.planey = -0.66;
	}
	if (curr->i == 'N')
	{
		all->player.dx = 0;
		all->player.dy = 1;
		all->player.planex = 0.66;
		all->player.planey = 0;
	}
	if (curr->i == 'S')
	{
		all->player.dx = 0;
		all->player.dy = -1;
		all->player.planex = -0.66;
		all->player.planey = 0;
	}
	/*
	if (curr->i == 'O').
	{
		while (++i < all->info.ennemies)
		{
			all->oeil[all->info.o][i].x = curr->x * 64;
			all->oeil[all->info.o][i].y = curr->y * 64;
			all->oeil[all->info.o][i].r = 18.0;
			all->oeil[all->info.o][i].reach = 100.0;			--------->          for identities geting their start positions.
			all->oeil[all->info.o][i].frameoeil = 0;
			all->oeil[all->info.o][i].frameoeill = 0;
		}
		all->info.o++;
	}
	get_c_p_info(curr, all);*/
	return (1);
}

int	check_close_map(t_map **map, t_info *info, t_all *all)
{
	(void) info;
	t_map	*curr;

	curr = *map;
	while (curr)
	{
		start_floodfill(curr, all);
		curr = curr->right;
	}
	return (1);
}

