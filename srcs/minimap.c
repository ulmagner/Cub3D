/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulysse <mulysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:41:29 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/25 15:42:43 by mulysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	copy_to_minimap(t_window *window, int x_ref,
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
	t_map	*col;
	t_color	color;

	int (y) = 0;
	int (l) = 0;
	t_map *(row) = all->map;
	while (row)
	{
		col = row;
		x = -20;
		while (col)
		{
			color = assign_color(color, col->i, &x);
			copy_to_minimap(&all->window, x, y, &color);
			if (col->x == all->info.column[l] - 1)
				break ;
			col = col->right;
		}
		l++;
		y += 20;
		if (col->y == all->info.line)
			break ;
		row = row->down;
	}
}
