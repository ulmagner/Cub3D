/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:46:24 by ulmagner          #+#    #+#             */
/*   Updated: 2025/03/31 12:11:17 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_window(t_all *all)
{
	all->window.main_w = 1920;
	all->window.main_h = 1010;
	all->window.mlx = mlx_init();
	if (!all->window.mlx)
		return (0);
	all->window.main = mlx_new_window(all->window.mlx, \
		all->window.main_w, all->window.main_h, "Cub3D");
	if (!all->window.main)
		return (0);
	return (1);
}

int	looping(t_all *all)
{
	t_player *(p) = &all->player;
	int (x) = -1;
	int (w) = all->window.main_w;
	while (x < w)
	{
		all->ray.camerax = 2 * x / (double)w - 1;
		all->ray.raydirx = p->dx + p->planex * all->ray.camerax;
		all->ray.raydiry = p->dy + p->planey * all->ray.camerax;
		x++;
	}
	// if (++(all->i) - all->frame < (int)(100 / 60))
	// 	return (0);
	// all->frame = all->i;
	// ft_bzero(all->game.addr, \
	// 	(all->game.w * all->game.h * all->game.bits_per_pixel / 8));
	// if (mlx_clear_window(all->window.mlx, all->window.main) < 0)
	// 	exit((ft_clearall(all), EXIT_FAILURE));
	// calcul_dist(all);
	// copy_ground_plan(all);
	// set_view_to_ppos(&all->view, &all->player, all);
	// if (!all->player.is_dead)
	// {
	// 	movement_handling(all);
	// 	action_handling(all, &all->attack, &all->counter);
	// }
	// if (!display_map(all, &all->window))
	// 	exit((ft_clearall(all), EXIT_FAILURE));
	return (1);
}

static int	close_window(t_all *all)
{
	return (exit((ft_clearall(all), EXIT_FAILURE)), 0);
}

int	hook_handling(t_all *all)
{
	// mlx_hook(all->window.main, 2, 1L << 0, movement_p, all);
	// mlx_hook(all->window.main, 3, 1L << 1, movement_r, all);
	// mlx_hook(all->window.main, 4, 1L << 2, action_p, all);
	// mlx_hook(all->window.main, 5, 1L << 3, action_r, all);
	mlx_hook(all->window.main, 17, 1L << 17, close_window, all);
	mlx_loop_hook(all->window.mlx, looping, all);
	mlx_loop(all->window.mlx);
	return (1);
}

int	launcher(t_all *all)
{
	if (!init_window(all))
		return (0);
	// if (!split_tile(all, &all->info, &all->fail))
	// 	return (0);
	// if (!init_bg(&all->ground, &all->plan, all, &all->window))
	// 	return (0);
	// if (!init_game(&all->game, &all->window, all))
	// 	return (0);
	// init_view(all, &all->view);
	// all->random.rd_floor = get_randoms(0, 1, 2);
	// all->info.collectible = all->info.coin;
	// all->player.animation = ft_calloc(9, sizeof(int));
	// if (!all->player.animation)
	// 	return (0);
	// build_ground(all);
	// init_distances(all, &all->info);
	// init_variables(all);
	if (!hook_handling(all))
		return (0);
	return (1);
}
