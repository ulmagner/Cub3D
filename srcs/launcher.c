/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:46:24 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/22 18:39:45 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

static int	engine_game(t_all *all)
{
	int (i) = -1;
	while (++i < all->info.box)
		render_3dsprite(all, &all->window, &all->boxes[i], &all->player);
	if (!all->player.access.status)
		render_3dsprite(all, &all->window, &all->player.access, &all->player);
	player_handling(all);
	movement_handling(all);
	if (all->movement.move[XK_m])
		minimap(all);
	mlx_put_image_to_window(all->window.mlx, all->window.main, \
		all->window.image.img, 0, 0);
	return (1);
}

int	looping(t_all *all)
{
	t_player *(p) = &all->player;
	t_raycasting *(r) = &all->ray;
	r->x = 0;
	p->ms = 0.2;
	if (++(all->i) - all->frame < (int)(100 / 60))
		return (0);
	all->time = get_current_time();
	double (dt) = all->time - all->oldtime;
	all->oldtime = all->time;
	ft_bzero(all->window.image.addr, \
		(all->window.main_w * all->window.main_h \
		* all->window.image.bits_per_pixel / 8));
	update_doors(all, dt);
	raycasting(all, p, r);
	if (!engine_game(all))
		exit((ft_clearall(all), EXIT_FAILURE));
	return (1);
}

int	launcher(t_all *all)
{
	if (!init_window(all))
		return (0);
	if (!split_tile(&all->tex, all))
		return (0);
	all->player.access.img = all->tex.tiles[2][0][0];
	all->player.access.img.scale = 7;
	all->player.access.img.mv = all->player.access.img.h;
	all->player.knife.animation = ft_calloc(2, sizeof(int));
	if (!all->player.knife.animation)
		return (0);
	all->open_progress = 0.0;
	int (i) = -1;
	while (++i < all->info.box)
	{
		all->boxes[i].img = all->tex.tiles[4][0][0];
		all->boxes[i].img.scale = 2;
		all->boxes[i].img.mv = all->boxes[i].img.h;
	}
	if (!all->player.knife.animation)
		return (0);
	if (!hook_handling(all))
		return (0);
	return (1);
}
