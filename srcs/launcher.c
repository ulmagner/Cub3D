/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:46:24 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/19 17:16:54 by ulmagner         ###   ########.fr       */
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

void	rotate_player(t_player *p, double angle)
{
	double (old_dx) = p->dx;
	double (old_planex) = p->planex;
	p->dx = p->dx * cos(angle) - p->dy * sin(angle);
	p->dy = old_dx * sin(angle) + p->dy * cos(angle);
	p->planex = p->planex * cos(angle) - p->planey * sin(angle);
	p->planey = old_planex * sin(angle) + p->planey * cos(angle);
}

void	copy_to_ground(t_window *window, int x_ref, int y_ref, t_color *color)
{
	int		c;
	int		x;
	int		y;

	y = -1;
	while (++y < 20)
	{
		x = -1;
		while (++x < 20)
		{
			c = (color->r << 16) | (color->g << 8) | (color->b);
			ft_pixel_put(window, x + x_ref, y + y_ref, c);
		}
	}
}

void	minimap(t_all *all)
{
	int		x;
	int		y;
	t_map	*row;
	t_map	*col;
	t_color	color;

	row = all->map;
	y = 0;
	while (row)
	{
		col = row;
		x = 0;
		while (col)
		{
			color = (t_color){254, 254, 254, 254};
			if (col->i == '1')
				color = (t_color){0, 0, 0, 0};
			if (col->i == 'N' || col->i == 'S' || col->i == 'E' || col->i == 'W')
				color = (t_color){0, 0, 0, 255};
			copy_to_ground(&all->window, x, y, &color);
			x += 20;
			if (col->x == all->info.column - 1)
				break ;
			col = col->right;
		}
		if (col->y == all->info.line - 1)
			break ;
		y += 20;
		row = row->down;
	}
}

int	mouse_move(int x, int y, t_all *all)
{
	t_player *(p) = &all->player;
	all->window.last_mouse_x = all->window.main_w / 2;
	all->window.last_mouse_y = all->window.main_h / 2;
	if (x != all->window.last_mouse_x && y != all->window.last_mouse_y)
	{
		int (delta_x) = x - all->window.last_mouse_x;
		int (delta_y) = y - all->window.last_mouse_y;
		all->window.mouse.x = (double)delta_x / (double)all->window.main_w * 20.0;
		all->window.mouse.y = (double)delta_y / (double)all->window.main_h * 10.0;
		double (rot_speed) = 0.003;
		double (angle) = all->window.mouse.x * rot_speed;
		if (x < all->window.mouse.x)
			angle = -angle;
		rotate_player(p, angle);
		mlx_mouse_move(all->window.mlx, all->window.main, all->window.main_w / 2, all->window.main_h / 2);
	}
	return (1);
}

void	render_2dsprite(t_window *win, t_image *weapon)
{
	int x_offset = win->main_w - weapon->w - 500;
	int y_offset = win->main_h - weapon->h - 70;
	int (x) = -1;
	int (y) = -1;

	while (++y < weapon->h)
	{
		x = -1;
		while (++x < weapon->w)
		{
			unsigned int color = get_pixel_color(weapon, x, y);
			if ((color & 0x00FFFFFF) == 0)
				continue;
			ft_pixel_put(win, x + x_offset, y + y_offset, color);
		}
	}
}

// void	render_3dsprite(t_all *all, t_card *s, t_image *tex)
// {
// 	double sprite_x = s->x - all->player.x;
// 	double sprite_y = s->y - all->player.y;

// 	// inverse camera matrix
// 	double inv_det = 1.0 / (all->player.planex * all->player.dy - all->player.dx * all->player.planey);
// 	double transform_x = inv_det * (all->player.dy * sprite_x - all->player.dx * sprite_y);
// 	double transform_y = inv_det * (-all->player.planey * sprite_x + all->player.planex * sprite_y);

// 	if (transform_y <= 0)
// 		return; // Sprite is behind the player

// 	int screen_x = (int)((all->window.main_w / 2) * (1 + transform_x / transform_y));

// 	int sprite_height = abs((int)(all->window.main_h / transform_y));
// 	int draw_start_y = -sprite_height / 2 + all->window.main_h / 2;
// 	int draw_end_y = sprite_height / 2 + all->window.main_h / 2;

// 	int sprite_width = sprite_height; // assuming square
// 	int draw_start_x = -sprite_width / 2 + screen_x;
// 	int draw_end_x = sprite_width / 2 + screen_x;

// 	double step = 1.0 * tex->h / sprite_height;
// 	double tex_pos = (draw_start_y - all->window.main_h / 2 + sprite_height / 2) * step;

// 	for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
// 	{
// 		if (stripe < 0 || stripe >= all->window.main_w)
// 			continue;
// 		if (transform_y >= all->zbuffer[stripe])
// 			continue;
// 		int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + screen_x)) * tex->w / sprite_width) / 256;

// 		double tex_y_pos = tex_pos;
// 		for (int y = draw_start_y; y < draw_end_y; y++)
// 		{
// 			if (y < 0 || y >= all->window.main_h)
// 				continue;
// 			int tex_y = (int)tex_y_pos & (tex->h - 1);
// 			tex_y_pos += step;

// 			unsigned int color = get_pixel_color(tex, tex_x, tex_y);
// 			if ((color & 0x00FFFFFF) != 0) // skip transparent
// 				ft_pixel_put(&all->window, stripe, y, color);
// 		}
// 	}
// }

int	looping(t_all *all)
{
	t_player *(p) = &all->player;
	t_map *(cp) = p->h;
	t_raycasting *(r) = &all->ray;
	r->x = 0;
	int (w) = all->window.main_w;
	p->ms = 0.2;
	ft_bzero(all->window.image.addr, \
		(all->window.main_w * all->window.main_h \
		* all->window.image.bits_per_pixel / 8));
	while (r->x < w)
	{
		cp = p->h;
		r->hit = false;
		set_playerpos_and_fov(p, r, w);
		init_dda(r, p);
		cp = dda_function(r, cp, '1');
		line_height_calculation(all, r, p);
		all->zbuffer[r->x] = r->perpwalldist;
		if (cp->i == '1')
			rendering_image(&all->tex.tiles[1][0][0], all, r->x, 1);
		r->y = r->drawend + 1;
		while (r->y < all->window.main_h)
		{
			float current_dist = all->window.main_h / (2.0 * r->y - all->window.main_h);
			float weight = current_dist / r->perpwalldist;
			float floor_x, floor_y;
			if (r->side == 0 && r->raydirx > 0)
			{
				floor_x = cp->x;
				floor_y = cp->y + r->tex_x;
			}
			else if (r->side == 0 && r->raydirx < 0)
			{
				floor_x = cp->x + 1.0;
				floor_y = cp->y + r->tex_x;
			}
			else if (r->side == 1 && r->raydiry > 0)
			{
				floor_x = cp->x + r->tex_x;
				floor_y = cp->y;
			}
			else
			{
				floor_x = cp->x + r->tex_x;
				floor_y = cp->y + 1.0;
			}
			float (cur_floor_x) = weight * floor_x + (1.0 - weight) * p->x;
			float (cur_floor_y) = weight * floor_y + (1.0 - weight) * p->y;
			int (tex_x) = (int)(cur_floor_x * TILE_SIZE) % TILE_SIZE;
			int (tex_y) = (int)(cur_floor_y * TILE_SIZE) % TILE_SIZE;
			int (color_floor) = get_pixel_color(&all->tex.tiles[1][1][0], tex_x, tex_y);
			ft_pixel_put(&all->window, r->x, r->y, color_floor);
			int (color_ceiling) = get_pixel_color(&all->tex.tiles[1][0][0], tex_x, tex_y);
			ft_pixel_put(&all->window, r->x, all->window.main_h - r->y, color_ceiling);
			r->y++;
		}
		cp = p->h;
		r->hit = false;
		init_dda(r, p);
		cp = dda_function(r, cp, 'B');
		line_height_calculation(all, r, p);
		if (cp && cp->i == 'B' && r->perpwalldist < all->zbuffer[r->x])
			rendering_image(&all->tex.tiles[4][0][0], all, r->x, 0.5);
		r->x++;
	}
	// render_3dsprite(all, &all->player.access, &all->player.access.img);

	if (!all->player.knife.normal || all->player.knife.aspect)
		all->player.knife.animation[all->player.knife.i] = (all->player.knife.animation[all->player.knife.i] + 1) % 37;
	else
		all->player.knife.animation[all->player.knife.i] = 5 + (all->player.knife.animation[all->player.knife.i] - 5 + 1) % 3;
	if (all->movement.move[XK_f])
	{
		all->player.knife.aspect = true;
		all->player.knife.animation[all->player.knife.i] = (all->player.knife.animation[all->player.knife.i] + 1) % 37;
	}
	if (all->player.knife.animation[all->player.knife.i] % 37 == 0)
		all->player.knife.lim++;
	if (all->player.knife.lim == 2)
	{
		all->player.knife.normal = true;
		all->player.knife.lim--;
		all->player.knife.aspect = false;
	}
	render_2dsprite(&all->window, &all->tex.tiles[3][all->player.knife.i][all->player.knife.animation[all->player.knife.i]]);
	all->oldtime = all->time;
	movement_handling(all);
	if (all->movement.move[XK_m])
		minimap(all);
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
	mlx_hook(all->window.main, 6, 1L << 6, mouse_move, all);
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
	all->player.access.img = all->tex.tiles[2][0][0];
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
