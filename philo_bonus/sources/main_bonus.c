/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:10:11 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/21 12:57:20 by mlitvino         ###   ########.fr       */
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
	init_sem(&forks, &info);
	create_philos(&philos, &info, &forks);
	wait_clean(&forks);
	return (0);
}
