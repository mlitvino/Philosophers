/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:10:11 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/13 16:16:27 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_philo		*philos;
	t_info		info;
	sem_t		*forks;

	philos = NULL;
	if (argc < 5)
		error("Error: wrong format");
	check_args(argc, argv, &info);
	forks = sem_open("/forks_sem", O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR | S_IXUSR, info.max_philos);
	if (forks == SEM_FAILED)
		error("Error: semaphore creation failed");
	philos = init_philos(philos, forks, &info);
	create_philos(philos, &info, forks);
	wait_clean(philos, forks, info.max_philos);
	return (0);
}
