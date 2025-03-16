/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:34:11 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/16 19:07:25 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_philo *philos, t_forks *forks, int max_i)
{
	int	i;

	i = 0;
	while (i < max_i)
	{
		pthread_mutex_destroy(&forks[i].fork_lock);
		i++;
	}
	pthread_mutex_destroy(&philos->info->print_lock);
}

void	join_clean(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->max_philos)
	{
		pthread_join(philos[i].philo_th, NULL);
		i++;
	}
	destroy_mutex(philos, philos->forks, info->max_philos);
	free(philos->forks);
	free(philos);
}
