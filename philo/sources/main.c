/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:10:11 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/11 20:03:29 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_forks	*forks;
	t_philo *philos;
	t_info	info;

	forks = NULL;
	philos = NULL;
	usleep(4);
	if (argc < 5)
		error("Error: wrong format");
	check_args(argc, argv, &info);
	forks = init_forks(forks, info.max_philos);
	philos = init_philos(philos, forks, &info);
	create_philos(philos, &info);
	join_clean(philos, &info);
	return (0);
}
