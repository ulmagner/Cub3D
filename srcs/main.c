/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:41:48 by ulmagner          #+#    #+#             */
/*   Updated: 2025/03/28 18:08:13 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_all	all;

	all = (t_all) {0};
	(void) ac;
	(void) av;
	if (!map_handling(&all.info, &all.map, &all.player, &all))
		return (ft_clearall(&all), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
