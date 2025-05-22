/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:41:54 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/22 11:43:52 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hit(t_map *tmp, t_raycasting *r, t_all *all, char c)
{
	if (tmp && (tmp->i == c || tmp->i == 'D'))
		r->hit = true;
	else if (tmp->i == 'd')
	{
		line_height_calculation(all, r, &all->player);
		if (all->open_progress > 0.0)
		{
			r->perpwalldist += all->open_progress;
			if (r->perpwalldist > 1)
				r->perpwalldist = 1;
			rendering_image(&all->tex.tiles[1][0][0], all, r->x, 0.5);
		}
	}
}
