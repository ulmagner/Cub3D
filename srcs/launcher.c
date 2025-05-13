/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:46:24 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/13 11:38:58 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_window(t_all *all)
{
	all->window.main_w = 1920;
	all->window.main_h = 1080;
	all->window.mlx = mlx_init();
	if (!all->window.mlx)
		return (0);
	all->window.main = mlx_new_window(all->window.mlx, \
		all->window.main_w, all->window.main_h, "Cub3D");
	if (!all->window.main)
		return (0);
	all->window.image.img = mlx_new_image(all->window.mlx, all->window.main_w, all->window.main_h);
	all->window.image.addr = mlx_get_data_addr(all->window.image.img, &all->window.image.bits_per_pixel, \
			&all->window.image.line_length, &all->window.image.endian);
	return (1);
}

void	set_playerpos_and_fov(t_player *p, t_raycasting *r, int x, int w)
{
	r->camerax = 2 * x / (double)w - 1;
	r->raydirx = p->dx + p->planex * r->camerax;
	r->raydiry = p->dy + p->planey * r->camerax;

	r->mapx = (int)r->x;
	r->mapy = (int)r->y;
}

void	rotate_player(t_player *p, int angle)
{
	double (old_dx) = p->dx;
	double (old_planex) = p->planex;
	p->dx = p->dx * cos(angle) - p->dy * sin(angle);
	p->dy = old_dx * sin(angle) + p->dy * cos(angle);
	p->planex = p->planex * cos(angle) - p->planey * sin(angle);
	p->planey = old_planex * sin(angle) + p->planey * cos(angle);
}

void	dda_function(t_raycasting *r, t_all *all)
{
	while (r->hit == 0)
	{
		if (r->sidedistx < r->sidedisty)
		{
			r->sidedistx += r->deltadistx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sidedisty += r->deltadisty;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (all->info.map[r->mapy * all->info.column + r->mapx] == '1')
			r->hit = 1;
	}
}

int	looping(t_all *all)
{
	t_player *(p) = &all->player;
	t_raycasting *(r) = &all->ray;

	int (x) = 0;
	int (w) = all->window.main_w;
	r->x = p->x;
	r->y = p->y;
	p->ms = 0.01;
	ft_bzero(all->window.image.addr, \
		(all->window.main_w * all->window.main_h \
		* all->window.image.bits_per_pixel / 8));

	while (x < w)
	{
		r->hit = 0;
		set_playerpos_and_fov(p, r, x, w);
		if (r->raydirx == 0)
			r->deltadistx = 1e30;
		else
			r->deltadistx = fabs(1 / r->raydirx);
		if (r->raydiry == 0)
			r->deltadisty = 1e30;
		else
			r->deltadisty = fabs(1 / r->raydiry);
		if (r->raydirx < 0)
			r->stepx = -1;
		else
			r->stepx = 1;
		if (r->stepx < 0)
			r->sidedistx = (r->x - r->mapx) * r->deltadistx;
		else
			r->sidedistx = (r->mapx + 1.0 - r->x) * r->deltadistx;

		if (r->raydiry < 0)
			r->stepy = -1;
		else
			r->stepy = 1;
		if (r->stepy < 0)
			r->sidedisty = (r->y - r->mapy) * r->deltadisty;
		else
			r->sidedisty = (r->mapy + 1.0 - r->y) * r->deltadisty;
		dda_function(r, all);

		if(r->side == 0)
			r->perpwalldist = (r->sidedistx - r->deltadistx);
		else
			r->perpwalldist = (r->sidedisty - r->deltadisty);

		r->lineheight = (int)(all->window.main_h / r->perpwalldist);
		r->drawstart = -r->lineheight / 2 + all->window.main_h / 2;
		if (r->drawstart < 0)
			r->drawstart = 0;
		r->drawend = r->lineheight / 2 + all->window.main_h / 2;
		if (r->drawend < 0)
			r->drawend = 0;
		if (r->drawend >= all->window.main_h)
			r->drawend = all->window.main_h - 1;

		t_map *(wall) = get_node_at(all->map, r->mapx, r->mapy);

		if (r->side == 0)
			r->tex_x = r->y + r->perpwalldist * r->raydiry;
		else
			r->tex_x = r->x + r->perpwalldist * r->raydirx;
		r->tex_x -= floor(r->tex_x);
		if (wall && wall->i == '1')
			rendering_image(&all->tex.tiles[0][0][0], all, x);

		int y = r->drawend + 1;
		while (y < all->window.main_h)
		{
			float current_dist = all->window.main_h / (2.0 * y - all->window.main_h);
		
			float weight = current_dist / r->perpwalldist;
		
			float floor_x, floor_y;
		
			if (r->side == 0 && r->raydirx > 0)
			{
				floor_x = r->mapx;
				floor_y = r->mapy + r->tex_x;
			}
			else if (r->side == 0 && r->raydirx < 0)
			{
				floor_x = r->mapx + 1.0;
				floor_y = r->mapy + r->tex_x;
			}
			else if (r->side == 1 && r->raydiry > 0)
			{
				floor_x = r->mapx + r->tex_x;
				floor_y = r->mapy;
			}
			else
			{
				floor_x = r->mapx + r->tex_x;
				floor_y = r->mapy + 1.0;
			}
		
			float cur_floor_x = weight * floor_x + (1.0 - weight) * p->x;
			float cur_floor_y = weight * floor_y + (1.0 - weight) * p->y;
		
			int tex_x = (int)(cur_floor_x * TILE_SIZE) % TILE_SIZE;
			int tex_y = (int)(cur_floor_y * TILE_SIZE) % TILE_SIZE;
		
			int color_floor = get_pixel_color(&all->tex.tiles[1][1][0], tex_x, tex_y);
			ft_pixel_put(&all->window, x, y, color_floor);

			int color_ceiling = get_pixel_color(&all->tex.tiles[1][0][0], tex_x, tex_y);
			ft_pixel_put(&all->window, x, all->window.main_h - y, color_ceiling);

			y++;
		}
		x++;
	}
	all->oldtime = all->time;

	mlx_mouse_get_pos(all->window.mlx, all->window.main, \
		&all->window.mouse.x, &all->window.mouse.y);
	// all->window.last_mouse_x = all->window.mouse.x;

	int (delta_x) = all->window.mouse.x - all->window.last_mouse_x;
	double (rot_speed) = 0.07;
	double (angle) = delta_x * rot_speed;

	if (delta_x != 0)
		rotate_player(p, angle);
	mlx_mouse_move(all->window.mlx, all->window.main, all->window.main_w / 2, all->window.main_h / 2);
	all->window.last_mouse_x = all->window.main_w / 2;
	// all->window.last_mouse_x = all->window.mouse.x;
	movement_handling(all);
	mlx_put_image_to_window(all->window.mlx, all->window.main, all->window.image.img, 0, 0);
	// if (++(all->i) - all->frame < (int)(100 / 60))
	// 	return (0);
	// all->frame = all->i;
	// ft_bzero(all->game.addr,
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
	mlx_hook(all->window.main, 2, 1L << 0, movement_p, all);
	mlx_hook(all->window.main, 3, 1L << 1, movement_r, all);
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
	if (!split_tile(&all->tex, all))
		return (0);
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
