/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:41:48 by ulmagner          #+#    #+#             */
/*   Updated: 2025/05/13 12:27:22 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_all	all;

	all = (t_all){0};
	if (!error_handling(ac, av, &all.info))
		return (ft_clearall(&all), EXIT_FAILURE);
	if (!get_paths(av[ac - 1], &all.tex))
		return (ft_clearall(&all), EXIT_FAILURE);
	if (!map_handling(&all.info, &all.map, &all))
		return (ft_clearall(&all), EXIT_FAILURE);
	if (!launcher(&all))
		return (ft_clearall(&all), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
