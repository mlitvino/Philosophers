/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DEL.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:00:27 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/11 19:27:45 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	notake_fork(t_philo *philos)
{
	philos->forks[0].fork = 0;
	philos->info->dth_time = 10;
}

void	*test(void *new)
{
	t_philo *philo = (t_philo *)new;

	if (philo->forks[0].fork == 1)
		philo->forks[0].fork = 0;
	else if (philo->forks[0].fork == 0)
		philo->forks[0].fork = 1;

	printf("Philo id - %d\n", philo->philo_id);
	printf("Philos fork - %d\n", philo->forks[0].fork);
	printf("Philos tim death - %d\n", philo->info->dth_time);
	printf("Philos time   to eat - %d\n", philo->info->eat_time);
	printf("Philos time to	  sleep - %d\n", philo->info->slp_time);
	printf("Max phil %d\n", philo->info->max_philos);
	printf("meals %d\n", philo->info->meals);
	printf("NEXT FELLA\n\n");
	return (0);
}

void	see_all(t_philo *philos)
{
	int i = 0;
	while (i < philos->info->max_philos)
	{
		printf("Philo id - %d\n", philos[i].philo_id);
		printf("Philos fork is set to - %d\n", philos[i].forks[i].fork);
		printf("Philos time to death - %d\n", philos[i].info->dth_time);
		printf("Philos time to eat - %d\n", philos[i].info->eat_time);
		printf("Philos time to sleep - %d\n", philos[i].info->slp_time);
		printf("Max philos - %d\n", philos[i].info->max_philos);
		printf("meals are  - %d\n", philos[i].info->meals);
		printf("NEXT FELLA\n\n");
		notake_fork(philos);
		i++;
	}
}

// see_all(philos);
// printf("Philos taken f adn d %d, %d \n", philos[0].forks[0].fork, philos[0].info->dth_time);
