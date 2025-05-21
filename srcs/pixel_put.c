/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:54:57 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/21 15:29:47 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_window *win, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= win->main_w || y >= win->main_h)
		return ;
	dst = win->image.addr \
		+ (y * win->image.line_length + x * (win->image.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel_color(t_image *image, int x, int y)
{
	char	*src;

	src = image->addr \
		+ ((y * image->line_length) + (x * image->bits_per_pixel / 8));
	return (*(unsigned int *)src);
}

void	rendering_image(t_image *tex, t_all *all, int xscreen, double scale)
{
	int	color;
	int	col_tex_y;

	t_raycasting *(r) = &all->ray;
	int (col_tex_x) = (int)(r->tex_x * (double)tex->w);
	if (col_tex_x < 0)
		return ;
	if ((r->side == 0 && r->raydirx > 0) || (r->side == 1 && r->raydiry < 0))
		col_tex_x = tex->w - col_tex_x - 1;
	int (scaled_line) = (int)(r->lineheight * scale);
	double (step) = 1.0 * tex->h / scaled_line;
	double (tex_pos) = (all->window.main_h / 2 - scaled_line / 2 \
		- all->window.main_h / 2 + r->lineheight / 2) * step;
	int (draw_start) = all->window.main_h / 2 - scaled_line / 2;
	int (draw_end) = draw_start + scaled_line;
	int (y) = draw_start;
	while (y < draw_end)
	{
		col_tex_y = (int)tex_pos & (tex->w - 1);
		tex_pos += step;
		color = get_pixel_color(tex, col_tex_x, col_tex_y);
		ft_pixel_put(&all->window, xscreen, y, color);
		y++;
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

void	render_3dsprite(t_all *all, t_window *win, t_obj *obj, t_player *p)
{
	obj->x = (obj->m->x + 0.5) - p->x;
	obj->y = (obj->m->y + 0.5) - p->y;
	double (invdet) = 1.0 / (p->planex * p->dy - p->dx * p->planey);
	double (transx) = invdet * (p->dy * obj->x - p->dx * obj->y);
	double (transy) = invdet * (-p->planey * obj->x + p->planex * obj->y);
	int (mvscreen_scale) = obj->h / 2;
	int (obj_screen_x) = (int)((win->main_w / 2) * (1 + transx / transy));

	obj->h = abs((int)(win->main_h / transy)) / obj->img.scale;
	int (draw_starty) = -obj->h / 2 + win->main_h / 2 + mvscreen_scale;
	if (draw_starty < 0) draw_starty = 0;
	int (draw_endy) = obj->h / 2 + win->main_h / 2 + mvscreen_scale;
	if (draw_endy >= win->main_h) draw_endy = win->main_h - 1;

	obj->w = abs((int)(win->main_h / transy)) / obj->img.scale;
	int (draw_startx) = -obj->w / 2 + obj_screen_x;
	if (draw_startx < 0) draw_startx = 0;
	int (draw_endx) = obj->w / 2 + obj_screen_x;
	if (draw_endx >= win->main_w) draw_endx = win->main_w - 1;

	for (int stripe = draw_startx; stripe < draw_endx; stripe++)
	{
		int (tex_x) = (int)(256 * (stripe - (-obj->w / 2 + obj_screen_x)) * obj->img.w / obj->w) / 256;
		if (transy > 0 && stripe > 0 && stripe < win->main_w && transy < all->zbuffer[stripe])
		for (int y = draw_starty; y < draw_endy; y++)
		{
			int d = (y - mvscreen_scale) * 256 - win->main_h * 128 + obj->h * 128;
			int tex_y = (((d * obj->img.h) / obj->h) / 256);
			unsigned int color = get_pixel_color(&obj->img, tex_x, tex_y);
			ft_pixel_put(win, stripe, y, color);
		}
	}
}
