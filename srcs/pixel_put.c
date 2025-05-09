/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:54:57 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/09 17:27:22 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_window *win, int x, int y, int color)
{
	char	*dst;

	// if (x < 0 || y < 0 || x >= win->main_w || y >= win->main_h)
	// 	return ;
	(void) x;
	(void) y;
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

void	rendering_image(t_image *tex, t_all *all, int xscreen)
{
	int	color;
	int	y;
	int	col_tex_x;
	int	step;
	int	tex_pos;
	int	col_tex_y;
	t_raycasting *(r) = &all->ray;

	col_tex_x = (int)(r->tex_x * (double)tex->w);
	if ((r->side == 0 && r->raydirx > 0) || (r->side == 1 && r->raydiry < 0))
		col_tex_x = tex->w - col_tex_x - 1;

	step = 1.0 * tex->h / r->lineheight;

	tex_pos = (r->drawstart - all->window.main_h / 2 + r->lineheight / 2) * step;

	y = r->drawstart;
	while (y <= r->drawend)
	{
		col_tex_y = (int)tex_pos & (tex->h - 1);
		tex_pos += step;
		color = get_pixel_color(tex, col_tex_x, col_tex_y);
		ft_pixel_put(&all->window, xscreen, y, color);
		y++;
	}
}
