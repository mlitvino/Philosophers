/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:10:11 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/19 17:54:53 by mlitvino         ###   ########.fr       */
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
	sem_unlink("/globl_dth_sem"); // DEL
	sem_unlink("/chk_fork_sem"); // DEL
	init_sem(&forks, &info);
	create_philos(&philos, &info, &forks);
	wait_clean(&forks);
	return (0);
}
