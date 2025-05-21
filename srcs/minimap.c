/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:41:29 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/21 17:55:55 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	copy_to_minimap(t_window *window, int x_ref, \
	int y_ref, t_color *color)
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

static t_color	assign_color(t_color color, char c, int *x)
{
	*x += 20;
	color = (t_color){254, 254, 254, 254};
	if (c == '1')
		color = (t_color){0, 0, 0, 0};
	if (c == 'B')
		color = (t_color){0, 255, 255, 0};
	if (c == 'D')
		color = (t_color){0, 0, 255, 255};
	if (c == 'd')
		color = (t_color){0, 255, 0, 255};
	if (c == 'C')
		color = (t_color){0, 0, 255, 0};
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		color = (t_color){0, 0, 0, 255};
	return (color);
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
		x = -20;
		while (col)
		{
			color = assign_color(color, col->i, &x);
			copy_to_minimap(&all->window, x, y, &color);
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
