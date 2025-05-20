/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:33:43 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/19 22:16:20 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_freewindow(t_window *window, t_all *all)
{
	// if (all->ground.img)
	// 	mlx_destroy_image(all->window.mlx, all->ground.img);
	// if (all->plan.img)
	// 	mlx_destroy_image(all->window.mlx, all->plan.img);
	// if (all->game.img)
	// 	mlx_destroy_image(all->window.mlx, all->game.img);
	(void) all;
	if (window->image.img)
		mlx_destroy_image(all->window.mlx, window->image.img);
	if (window->mlx)
	{
		if (window->main)
			mlx_destroy_window(window->mlx, window->main);
		mlx_destroy_display(window->mlx);
		free(window->mlx);
	}
}


static void	ft_freeimage(t_all *all, int i)
{
	int	j;
	int	a;

	int (b) = 0;
	if (!all->tex.tiles || !*all->tex.tiles)
		return ;
	while (++i < all->tex.nbr_image)
	{
		j = -1;
		while (++j < all->tex.nbr_i[i])
		{
			a = -1;
			while (++a < all->tex.nbr_a[b])
				mlx_destroy_image(all->window.mlx,
					all->tex.tiles[i][j][a].img);
			b++;
			free(all->tex.tiles[i][j]);
		}
		free(all->tex.tiles[i]);
	}
	free(all->tex.tiles);
}

void	ft_clearall(t_all *all)
{
	int	(i) = -1;
	ft_freemap(&all->map);
	ft_freeplayer(&all->player);
	/*
	if (all->trap)
		free(all->trap);
	if (all->slime)
		free(all->slime);
	if (all->oeil)
	{
		while (++i < all->info.oeil)
			if (all->oeil[i])
				free(all->oeil[i]);
		free(all->oeil);
	}
	i = -1;
	free(all->dist.p_c);
	free(all->dist.p_t);
	free(all->dist.p_o);*/
	ft_freeimage(all, i);
	ft_freeinfo(&all->info);
	ft_freetex(&all->tex);
	ft_freewindow(&all->window, all);
	close(all->info.fd);
}

