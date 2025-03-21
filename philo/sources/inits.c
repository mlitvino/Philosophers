/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:01:52 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/21 17:26:48 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo(void *new_philo)
{
	t_philo *philo;

	philo = new_philo;
	philo->dth_date = get_usec(&philo->tv) + philo->info->dth_time;
	pthread_mutex_lock(&philo->info->print_lock);
	if (philo->info->death != 1)
		printf("%lld %d has taken a fork\n",
			get_msec(&philo->tv), philo->philo_id);
	pthread_mutex_unlock(&philo->info->print_lock);
	while (is_dead(philo, philo->info) != -1)
	{
		pthread_mutex_unlock(&philo->info->print_lock);
		usleep(250);
	}
	return (0);
}

t_philo	*init_philos(t_philo *philos, t_forks *forks, t_info *info)
{
	int	i;

	philos = malloc(sizeof(t_philo) * info->max_philos);
	if (!philos)
	{
		destroy_mutex(philos, forks, info->max_philos);
		free(forks);
		return (error("Error: malloc failed in init_philos"), NULL);
	}
	i = 0;
	while (i < info->max_philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].forks = forks;
		philos[i].info = info;
		philos[i].left = i;
		philos[i].right = (i + 1) % info->max_philos;
		i++;
	}
	return (philos);
}

t_forks	*init_forks(t_philo *philos, t_forks *forks, t_info *info)
{
	int	i;
	int	res;

	forks = malloc(sizeof(t_forks) * info->max_philos);
	if (!forks)
		return (error("Error: malloc failed in init_forks"), NULL);
	if (pthread_mutex_init(&info->print_lock, NULL) != 0)
		return (error("Error: mutex failed init"), free(forks), NULL);
	i = 0;
	while (i < info->max_philos)
	{
		forks[i].fork = 1;
		forks[i].queue = 0;
		res = pthread_mutex_init(&forks[i].fork_lock, NULL);
		if (res != 0)
		{
			destroy_mutex(philos, forks, i);
			free(forks);
			return (error("Error: mutex failed init"), NULL);
		}
		i++;
	}
	return (forks);
}

int	create_philos(t_philo *philos, t_info *info)
{
	int	i;
	int	res;

	i = 0;
	while (i < info->max_philos)
	{
		res = pthread_create(&philos[i].philo_th, NULL,
				routine, (void *)&philos[i]);
		if (res != 0)
		{
			info->stop_flag = 1;
			info->max_philos = i;
			join_clean(philos, info);
			return (error("Error: thread creation failed"), -1);
		}
		i++;
	}
	return (0);
}
