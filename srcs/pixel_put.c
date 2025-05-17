/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:54:57 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/18 00:58:16 by ulmagner         ###   ########.fr       */
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

// void	rendering_image(t_image *tex, t_all *all, int xscreen, double scale)
// {
// 	int	color;
// 	int	col_tex_y;
// 	t_raycasting *(r) = &all->ray;

// 	int (col_tex_x) = (int)(r->tex_x * (double)tex->w);
// 	if (col_tex_x < 0)
// 		return ;
// 	if ((r->side == 0 && r->raydirx > 0) || (r->side == 1 && r->raydiry < 0))
// 		col_tex_x = tex->w - col_tex_x - 1;
// 	int (scaled_line) = (int)(r->lineheight * scale);
// 	double (step) = 1.0 * tex->h / scaled_line;
// 	double (tex_pos) = (all->window.main_h / 2 - scaled_line / 2 - all->window.main_h / 2 + r->lineheight / 2) * step;
// 	int (draw_start) = all->window.main_h / 2 - scaled_line / 2;
// 	int (draw_end) = draw_start + scaled_line;
// 	int (y) = draw_start;
// 	while (y < draw_end)
// 	{
// 		col_tex_y = (int)tex_pos & (tex->w - 1);
// 		tex_pos += step;
// 		color = get_pixel_color(tex, col_tex_x, col_tex_y);
// 		ft_pixel_put(&all->window, xscreen, y, color);
// 		y++;
// 	}
// }

void	rendering_image(t_image *tex, t_all *all, int xscreen, double scale)
{
	int	color;
	int	col_tex_y;
	t_raycasting *r = &all->ray;

	int col_tex_x = (int)(r->tex_x * (double)tex->w);
	if (col_tex_x < 0)
		return;
	if ((r->side == 0 && r->raydirx > 0) || (r->side == 1 && r->raydiry < 0))
		col_tex_x = tex->w - col_tex_x - 1;

	// Compute scaled height
	int scaled_height = (int)(r->lineheight * scale);

	// Align bottom with the actual floor (original drawend)
	int draw_end = r->drawend;
	int draw_start = draw_end - scaled_height;
	if (draw_start < 0)
		draw_start = 0;

	double step = 1.0 * tex->h / scaled_height;
	double tex_pos = 0;

	for (int y = draw_start; y < draw_end; y++)
	{
		col_tex_y = (int)tex_pos & (tex->h - 1);
		tex_pos += step;
		color = get_pixel_color(tex, col_tex_x, col_tex_y);
		if ((color & 0x00FFFFFF) != 0)
			ft_pixel_put(&all->window, xscreen, y, color);
	}
}
