/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:10:11 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/13 12:58:08 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_forks	*forks;
	t_philo *philos;
	t_info	info;

	forks = NULL;
	philos = NULL;
	if (argc < 5)
		error("Error: wrong format");
	check_args(argc, argv, &info);
	forks = init_forks(forks, info.max_philos);
	if (!forks)
		return (-1);
	philos = init_philos(philos, forks, &info);
	if (!philos)
		return (-1);
	if (create_philos(philos, &info) == -1)
		return (-1);
	join_clean(philos, &info);
	return (0);
}
