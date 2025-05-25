/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulysse <mulysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 23:15:58 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/25 15:47:21 by mulysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rendering_image(t_image *tex, t_all *all, int xscreen, double scale)
{
	int (color) = 0;
	int (col_tex_y) = 0;
	t_raycasting *(r) = &all->ray;
	int (col_tex_x) = (int)(r->tex_x * (double)tex->w);
	if (col_tex_x < 0)
		return ;
	if ((r->side == 0 && r->raydirx > 0) || (r->side == 1 && r->raydiry < 0))
		col_tex_x = tex->w - col_tex_x - 1;
	int (scaled_line) = (int)(r->lineheight * scale);
	double (step) = 1.0 * tex->h / scaled_line;
	double (tex_pos) = (all->window.main_h / 2 - scaled_line / 2
			- all->window.main_h / 2 + r->lineheight / 2) * step;
	int (draw_start) = all->window.main_h / 2 - scaled_line / 2;
	int (draw_end) = draw_start + scaled_line;
	int (y) = draw_start - 1;
	while (++y < draw_end)
	{
		col_tex_y = (int)tex_pos & (tex->w - 1);
		tex_pos += step;
		color = get_pixel_color(tex, col_tex_x, col_tex_y);
		if ((color & 0x00FFFFFF) == 0)
			continue ;
		ft_pixel_put(&all->window, xscreen, y, color);
	}
}

void	render_2dsprite(t_window *win, t_image *weapon)
{
	unsigned int	color;

	int (x_offset) = win->main_w - weapon->w - 500;
	int (y_offset) = win->main_h - weapon->h - 70;
	int (x) = -1;
	int (y) = -1;
	while (++y < weapon->h)
	{
		x = -1;
		while (++x < weapon->w)
		{
			color = get_pixel_color(weapon, x, y);
			if ((color & 0x00FFFFFF) == 0)
				continue ;
			ft_pixel_put(win, x + x_offset, y + y_offset, color);
		}
	}
}

static void	draw_sprite(t_obj *obj, t_all *all, t_window *win, double transy)
{
	int (stripe) = obj->draw_startx - 1;
	int (y) = 0;
	int (tex_x) = 0;
	int (d) = 0;
	unsigned int (color) = 0;
	int (tex_y) = 0;
	while (++stripe < obj->draw_endx)
	{
		tex_x = (int)(256 * (stripe - (-obj->w / 2 + obj->img.obj_screen_x))
				* obj->img.w / obj->w) / 256;
		if (transy > 0 && stripe > 0 && stripe < win->main_w
			&& transy < all->zbuffer[stripe])
		{
			y = obj->draw_starty - 1;
			while (++y < obj->draw_endy)
			{
				d = (y - obj->img.mvscreen_scale) * 256
					- win->main_h * 128 + obj->h * 128;
				tex_y = (((d * obj->img.h) / obj->h) / 256);
				color = get_pixel_color(&obj->img, tex_x, tex_y);
				if ((color & 0x00FFFFFF) != 0)
					ft_pixel_put(win, stripe, y, color);
			}
		}
	}
}

void	render_3dsprite(t_all *all, t_window *win, t_obj *obj, t_player *p)
{
	obj->x = (obj->m->x + 0.5) - p->x;
	obj->y = (obj->m->y + 0.5) - p->y;
	double (invdet) = 1.0 / (p->planex * p->dy - p->dx * p->planey);
	double (transx) = invdet * (p->dy * obj->x - p->dx * obj->y);
	double (transy) = invdet * (-p->planey * obj->x + p->planex * obj->y);
	obj->img.mvscreen_scale = obj->h / 2;
	obj->img.obj_screen_x = (int)((win->main_w / 2) * (1 + transx / transy));
	obj->h = abs((int)(win->main_h / transy)) / obj->img.scale;
	obj->draw_starty = -obj->h / 2 + win->main_h / 2 + obj->img.mvscreen_scale;
	if (obj->draw_starty < 0)
		obj->draw_starty = 0;
	obj->draw_endy = obj->h / 2 + win->main_h / 2 + obj->img.mvscreen_scale;
	if (obj->draw_endy >= win->main_h)
		obj->draw_endy = win->main_h - 1;
	obj->w = abs((int)(win->main_h / transy)) / obj->img.scale;
	obj->draw_startx = -obj->w / 2 + obj->img.obj_screen_x;
	if (obj->draw_startx < 0)
		obj->draw_startx = 0;
	obj->draw_endx = obj->w / 2 + obj->img.obj_screen_x;
	if (obj->draw_endx >= win->main_w)
		obj->draw_endx = win->main_w - 1;
	draw_sprite(obj, all, win, transy);
}
