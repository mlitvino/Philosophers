/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:01:52 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/11 19:04:55 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(t_philo *philos, t_forks *forks, t_info *info)
{
	int	i;

	philos = malloc(sizeof(t_philo) * info->max_philos);
	if (!philos)
	{
		free(forks);
		error("Error: malloc failed in init_philos");
	}
	i = 0;
	while (i < info->max_philos)
	{
		philos[i].philo_id = i;
		philos[i].forks = forks;
		philos[i].info = info;
		philos[i].left = i;
		philos[i].right = i % info->max_philos - 1;
		i++;
	}
	return (philos);
}

t_forks	*init_forks(t_forks *forks, int max_philos)
{
	int	i;
	int	res;

	forks = malloc(sizeof(t_forks) * max_philos);
	if (!forks)
		error("Error: malloc failed in init_forks");
	i = 0;
	while (i < max_philos)
	{
		forks[i].fork = 1;
		res = pthread_mutex_init(&forks[i].lock, NULL);
		if (res != 0)
		{
			free(forks);
			destroy_mutex(forks, i);
			error("Error: mutex failed init");
		}
		i++;
	}
	return (forks);
}

void	create_philos(t_philo *philos, t_info *info)
{
	int	i;
	int	res;

	i = 0;
	while (i < info->max_philos)
	{
		res = pthread_create(&philos[i].philo_th, NULL, test, &philos[i]);
		if (res != 0)
		{
			info->stop_flag = 1;
			info->max_philos = i + 1;
			join_clean(philos, info);
			error("Error: thread creation failed");
		}
		i++;
	}
}
