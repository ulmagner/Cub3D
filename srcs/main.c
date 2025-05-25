/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mulysse <mulysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:41:48 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/25 15:55:19 by mulysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_all	all;

	all = (t_all){0};
	all.floor.r = -1;
	all.ceiling.r = -1;
	if (!error_handling(ac, av, &all.info))
		return (ft_clearall(&all), EXIT_FAILURE);
	if (!map_handling(&all.info, &all.map, &all))
		return (ft_clearall(&all), EXIT_FAILURE);
	close(all.info.fd);
	if (!get_paths(av[ac - 1], &all.tex))
		return (ft_clearall(&all), EXIT_FAILURE);
	if (!launcher(&all))
		return (ft_clearall(&all), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
