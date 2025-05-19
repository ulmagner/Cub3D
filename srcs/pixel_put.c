/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:54:57 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/19 14:00:17 by ulmagner         ###   ########.fr       */
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

	int (col_tex_x) = (int)(r->tex_x * tex->w);
	if (col_tex_x < 0)
		return ;
	if ((r->side == 0 && r->raydirx > 0) || (r->side == 1 && r->raydiry < 0))
		col_tex_x = tex->w - col_tex_x - 1;
	int (scaled_line) = (int)(r->lineheight * scale);
	double (step) = 1.0 * tex->h / scaled_line;
	int (draw_end) = r->drawend;
	int (draw_start) = draw_end - scaled_line;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= all->window.main_h)
		draw_end = all->window.main_h - 1;
	// double tex_pos = (draw_start < 0) ? (-draw_start) * step : 0;
	// double tex_pos = (draw_start < r->drawend - scaled_line) ? (draw_start - (r->drawend - scaled_line)) * step : 0;
	double tex_pos = (draw_start - (r->drawend - scaled_line)) * step;
	if (tex_pos < 0)
		tex_pos = 0;
	int (y) = draw_start;
	while (y < draw_end)
	{
		col_tex_y = (int)tex_pos & (tex->h - 1);
		tex_pos += step;
		color = get_pixel_color(tex, col_tex_x, col_tex_y);
		ft_pixel_put(&all->window, xscreen, y, color);
		y++;
	}
}
