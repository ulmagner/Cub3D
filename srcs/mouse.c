/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulysse <mulysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:47:09 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/25 15:43:34 by mulysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_player(t_player *p, double angle)
{
	double (old_dx) = p->dx;
	double (old_planex) = p->planex;
	p->dx = p->dx * cos(angle) - p->dy * sin(angle);
	p->dy = old_dx * sin(angle) + p->dy * cos(angle);
	p->planex = p->planex * cos(angle) - p->planey * sin(angle);
	p->planey = old_planex * sin(angle) + p->planey * cos(angle);
}

int	mouse_move(int x, int y, t_all *all)
{
	int		delta_x;
	int		delta_y;
	double	rot_speed;
	double	angle;

	t_player *(p) = &all->player;
	all->window.last_mouse_x = all->window.main_w / 2;
	all->window.last_mouse_y = all->window.main_h / 2;
	if (x != all->window.last_mouse_x && y != all->window.last_mouse_y)
	{
		delta_x = x - all->window.last_mouse_x;
		delta_y = y - all->window.last_mouse_y;
		all->window.mouse.x = (double)delta_x
			/ (double)all->window.main_w * 20.0;
		all->window.mouse.y = (double)delta_y
			/ (double)all->window.main_h * 10.0;
		rot_speed = 0.006;
		angle = all->window.mouse.x * rot_speed;
		if (x < all->window.mouse.x)
			angle = -angle;
		rotate_player(p, angle);
		mlx_mouse_move(all->window.mlx, all->window.main,
			all->window.main_w / 2, all->window.main_h / 2);
	}
	return (1);
}
