/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:10:11 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/13 23:35:42 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

#include <errno.h>
void pe_error(const char *msg) {
    perror(msg);  // This will print the error message according to errno
    exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_philo		*philos;
	t_info		info;
	t_my_sem	forks;

	philos = NULL;
	if (argc < 5)
		error("Error: wrong format");
	check_args(argc, argv, &info);
	sem_unlink("/forks_sem"); // DEL
	sem_unlink("/lock_sem"); // DEL
	init_sem(&forks, &info);
	philos = init_philos(philos, &forks, &info);
	create_philos(philos, &info, &forks);
	wait_clean(philos, &forks, info.max_philos);
	return (0);
}
