/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:46:24 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/20 18:24:32 by ulmagner         ###   ########.fr       */
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
			if (col->i == 'B')
				color = (t_color){0, 255, 255, 0};
			if (col->i == 'D')
				color = (t_color){0, 0, 255, 255};
			if (col->i == 'C' && !all->player.access.status)
				color = (t_color){0, 0, 255, 0};
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
		all->window.mouse.x = (double)delta_x\
			/ (double)all->window.main_w * 20.0;
		all->window.mouse.y = (double)delta_y\
			/ (double)all->window.main_h * 10.0;
		rot_speed = 0.03;
		angle = all->window.mouse.x * rot_speed;
		if (x < all->window.mouse.x)
			angle = -angle;
		rotate_player(p, angle);
		mlx_mouse_move(all->window.mlx, all->window.main,\
			all->window.main_w / 2, all->window.main_h / 2);
	}
	return (1);
}

double get_current_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

int	looping(t_all *all)
{
	t_player *(p) = &all->player;
	t_map *(cp) = p->h;
	t_raycasting *(r) = &all->ray;
	r->x = 0;
	int (w) = all->window.main_w;
	p->ms = 0.1;
	if (++(all->i) - all->frame < (int)(100 / 60))
		return (0);
	all->time = get_current_time();
	double (dt) = all->time - all->oldtime;
	all->oldtime = all->time;
	ft_bzero(all->window.image.addr, \
		(all->window.main_w * all->window.main_h \
		* all->window.image.bits_per_pixel / 8));
	update_doors(all, dt);
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
		if (cp->i == 'D' && all->open_progress < 1.0)
		{
			r->perpwalldist -= all->open_progress;
			if (r->perpwalldist < 0)
				r->perpwalldist = 0;
			rendering_image(&all->tex.tiles[1][0][0], all, r->x, 0.5);
		}
		r->y = r->drawend + 1;
		while (r->y < all->window.main_h)
			floor_ceiling_raycasting(all, r, cp, p);
		r->x++;
	}
	int (i) = -1;
	while (++i < all->info.box)
		render_3dsprite(all, &all->window, &all->boxes[i], &all->player);
	if (!all->player.access.status)
		render_3dsprite(all, &all->window, &all->player.access, &all->player);
	player_handling(all);
	movement_handling(all);
	if (all->movement.move[XK_m])
		minimap(all);
	mlx_put_image_to_window(all->window.mlx, all->window.main, all->window.image.img, 0, 0);
	// if (!display_map(all, &all->window))
	// 	exit((ft_clearall(all), EXIT_FAILURE));
	return (1);
}

int	launcher(t_all *all)
{
	if (!init_window(all))
		return (0);
	if (!split_tile(&all->tex, all))
		return (0);
	all->player.access.img = all->tex.tiles[2][0][0];
	all->player.access.img.scale = 2.3;
	all->player.access.img.mv = all->player.access.img.h;
	all->player.knife.animation = ft_calloc(2, sizeof(int));
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
