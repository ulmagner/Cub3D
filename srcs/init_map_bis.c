/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:12:09 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/15 10:41:58 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_dynamique_info(t_map *node, t_info *info, t_all *all)
{
	(void) all;
	(void) info;
	//j = -1;
	if (node->i == 'N' || node->i == 'W' || node->i == 'S' || node->i == 'E')
	{
		all->player.h = node;
		all->player.x = info->i_x;
		all->player.y = info->i_y;
	}
	/*
	if (node->i == 'O')
	{
		while (++j < info->ennemies)
				(all->oeil[all->info.o][j]).o = node;         ------->      identities positions on the lst_map.
		all->info.o++;
	}
	if (node->i == 'C')
		(all->slime[info->slime++]).c = node;
	if (node->i == 'F')
		(all->trap[info->fire++]).t = node;*/
	return (1);
}

static t_map	*ft_newnode(t_info *info, int *i, t_all *all)
{
	t_map	*node;

	node = malloc(sizeof(t_map));
	if (!node)
		return (NULL);
	node->i = info->map[*i];
	node->is_visited = 0;
	node->x = info->i_x;
	node->y = info->i_y;
	node->x_pxl = node->x * 64;
	node->y_pxl = node->y * 64;
	node->right = NULL;
	node->left = NULL;
	node->up = NULL;
	node->down = NULL;
	get_dynamique_info(node, info, all);
	return (node);
}

void	chain_map(t_map **curr, t_map **head, t_map *node)
{
	if (!(*head))
	{
		*head = node;
		*curr = *head;
	}
	else
	{
		(*curr)->right = node;
		node->left = *curr;
		*curr = node;
	}
}

void	chain_map_updown(t_map *node, t_info *info, t_map **head, t_map **curr)
{
	t_map	*temp;

	if (info->i_y == 0)
		node->up = NULL;
	else
	{
		temp = *head;
		while (temp && (temp->x != node->x || temp->y != node->y - 1))
			temp = temp->right;
		if (temp)
		{
			node->up = temp;
			temp->down = node;
		}
	}
	*curr = node;
}

int	make_list(int *i, t_map **node, t_all *all)
{
	if (all->info.i_x == all->info.column)
	{
		all->info.i_x = 0;
		all->info.i_y++;
		(*i)++;
	}
	*node = ft_newnode(&all->info, i, all);
	all->info.i_x++;
	if (!*node)
		return (0);
	return (1);
}

