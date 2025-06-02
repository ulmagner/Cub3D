/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:12:09 by ulmagner          #+#    #+#             */
/*   Updated: 2025/06/02 10:46:39 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_dynamique_info(t_map *node, t_info *info, t_all *all)
{
	if (node->i == 'N' || node->i == 'W' || node->i == 'S' || node->i == 'E')
	{
		all->player.h = node;
		all->player.x = info->i_x;
		all->player.y = info->i_y;
		all->player.knife.i = 0;
		all->player.knife.normal = false;
		all->player.knife.lim = 0;
		all->player.knife.aspect = false;
		all->player.knife.frame_delay = 0;
	}
	if (node->i == 'B')
	{
		all->boxes[info->box].x = node->x;
		all->boxes[info->box].y = node->y;
		all->boxes[info->box].status = 0;
		all->boxes[info->box++].m = node;
	}
	if (node->i == 'D')
	{
		all->door.m = node;
		all->door.status = 0;
	}
	return (1);
}

static t_map	*ft_newnode(t_info *info, t_all *all)
{
	t_map	*node;

	node = malloc(sizeof(t_map));
	if (!node)
		return (NULL);
	node->i = info->sp_map[info->i_y][info->i_x];
	node->is_visited = 0;
	node->x = info->i_x;
	node->y = info->i_y;
	node->right = NULL;
	node->left = NULL;
	node->up = NULL;
	node->down = NULL;
	if (node->i == 'C')
	{
		all->player.access.status = 0;
		all->player.access.m = node;
		all->player.access.x = info->i_x;
		all->player.access.y = info->i_y;
	}
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

int	make_list(t_map **node, t_all *all)
{
	*node = ft_newnode(&all->info, all);
	if (!*node)
		return (0);
	return (1);
}
