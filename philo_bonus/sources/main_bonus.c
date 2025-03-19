/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:10:11 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/18 18:27:26 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void	*wait_death(void *new_philo)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)new_philo;
// 	//sem_t *forks = sem_open("/forks_sem", 0);
// 	sem_wait(philo->forks->globl_dth);
// 	printf("SUCCESS\n");
// 	philo->globl_death = 1;
// 	sem_post(philo->forks->globl_dth);
// 	return (0);
// }

	// philos.forks = &forks;
	// if (pthread_create(&philos.wait_dth_thrd, NULL, wait_death, (void *)&philos) == -1)
	// {
	// 	//proc_exit_clean(forks);
	// 	exit(1);
	// }
	// pthread_detach(philos.wait_dth_thrd);
	// sem_post(forks.globl_dth);
	// sleep(3);
	// clean_sem(&philos, &forks, 1);

// test sem leaks

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
	sem_unlink("/globl_dth_sem"); // DEL
	sem_unlink("/chk_fork_sem"); // DEL
	init_sem(&forks, &info);
	create_philos(&philos, &info, &forks);
	wait_clean(&forks);
	return (0);
}
