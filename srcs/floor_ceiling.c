/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:34:42 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/23 12:27:03 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_floor_ceiling(t_raycasting *r, t_map *cp, \
	float *floor_x, float *floor_y)
{
	if (r->side == 0 && r->raydirx > 0)
	{
		*floor_x = cp->x;
		*floor_y = cp->y + r->tex_x;
	}
	else if (r->side == 0 && r->raydirx < 0)
	{
		*floor_x = cp->x + 1.0;
		*floor_y = cp->y + r->tex_x;
	}
	else if (r->side == 1 && r->raydiry > 0)
	{
		*floor_x = cp->x + r->tex_x;
		*floor_y = cp->y;
	}
	else
	{
		*floor_x = cp->x + r->tex_x;
		*floor_y = cp->y + 1.0;
	}
}

// printf("%d %d %d\n", all->floor.r, all->floor.g, all->floor.b);
// unsigned int(color) = (all->floor.r << 16) | (all->floor.g << 8) | all->floor.b;
// ft_pixel_put(&all->window, r->x, all->window.main_h - r->y, color);
// color = (all->ceiling.r << 16) | (all->ceiling.g << 8) | all->ceiling.b;
//  ft_pixel_put(&all->window, r->x, r->y, color);
void floor_ceiling_raycasting(t_all *all, t_raycasting *r,
								t_map *cp, t_player *p)
{
	float(current_dist) = all->window.main_h / (2.0 * r->y - all->window.main_h);
	float(weight) = current_dist / r->perpwalldist;
	float(floor_x) = 0;
	float(floor_y) = 0;
	init_floor_ceiling(r, cp, &floor_x, &floor_y);
	float(cur_floor_x) = weight * floor_x + (1.0 - weight) * p->x;
	float(cur_floor_y) = weight * floor_y + (1.0 - weight) * p->y;
	int(tex_x) = (int)(cur_floor_x * TILE_SIZE) % TILE_SIZE;
	int(tex_y) = (int)(cur_floor_y * TILE_SIZE) % TILE_SIZE;
	int(color_floor) = get_pixel_color(&all->tex.tiles[0][1][0], tex_x, tex_y);
	ft_pixel_put(&all->window, r->x, r->y, color_floor);
	int(color_ceiling) = get_pixel_color(&all->tex.tiles[0][0][0], tex_x, tex_y);
	ft_pixel_put(&all->window, r->x, all->window.main_h - r->y, color_ceiling);
	r->y++;
}
