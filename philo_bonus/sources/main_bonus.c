/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:10:11 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/16 23:56:34 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_philo		philos;
	t_info		info;
	t_my_sem	forks;

	if (argc < 5)
		error("Error: wrong format");
	check_args(argc, argv, &info);
	sem_unlink("/forks_sem"); // DEL
	sem_unlink("/lock_sem"); // DEL
	sem_unlink("/print_sem"); // DEL
	init_sem(&philos, &forks, &info);
	philos.forks = &forks;
	philos.info = &info;
	create_philos(&philos, &info, &forks);
	wait_clean(&philos, &forks, info.max_philos);
	return (0);
}
