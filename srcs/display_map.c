/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:52:55 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/20 18:59:36 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*get_node_at(t_map *head, int x, int y)
{
	t_map *(tmp) = head;
	while (tmp)
	{
		if (tmp->x == x && tmp->y == y)
			return (tmp);
		if (tmp->right)
			tmp = tmp->right;
		else if (tmp->down)
			tmp = tmp->down;
		else
			break ;
	}
	return (NULL);
}
