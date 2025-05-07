/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:54:39 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/07 17:29:59 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int movement_p(int keycode, t_all *all)
{
	all->movement.move[keycode] = true;
	if (keycode == XK_Escape)
		exit((ft_clearall(all), EXIT_SUCCESS));
	return (0);
}

int	movement_r(int keycode, t_all *all)
{
	all->movement.move[keycode] = false;
	// check_mouvment(&all->player);
	return (0);
}

int	movement_handling(t_all *all)
{
    dir_up(&all->player, &all->movement, all);
    dir_down(&all->player, &all->movement, all);
    dir_left(&all->player, &all->movement, all);
    dir_right(&all->player, &all->movement, all);
    // all->frameplayer = all->i;
    if (all->movement.move[XK_e])
	{
        exit((ft_clearall(all), EXIT_FAILURE));
	}
	return (1);
}
