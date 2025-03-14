/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:18:25 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/14 17:04:49 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	put_forks(t_philo *philo)
{
	philo->forks[philo->left].fork = 1;
	if (is_dead(philo, philo->info) == -1)
	{
		pthread_mutex_unlock(&philo->forks[philo->right].fork_lock);
		return (-1);
	}
	printf("%lld %d put a fork down\n", philo->temp_time, philo->philo_id);
	pthread_mutex_unlock(&philo->info->print_lock);
	pthread_mutex_unlock(&philo->forks[philo->right].fork_lock);
	philo->forks[philo->right].fork = 1;
	if (is_dead(philo, philo->info) == -1)
	{
		pthread_mutex_unlock(&philo->forks[philo->left].fork_lock);
		return (-1);
	}
	printf("%lld %d put a fork down\n", philo->temp_time, philo->philo_id);
	pthread_mutex_unlock(&philo->info->print_lock);
	pthread_mutex_unlock(&philo->forks[philo->left].fork_lock);
	return (0);
}

int	take_fork(t_philo *philo, t_forks *forks, int fork_i)
{
	pthread_mutex_lock(&forks[fork_i].fork_lock);
	pthread_mutex_lock(&philo->info->print_lock);
	if (is_dead(philo, philo->info) == -1)
	{
		pthread_mutex_unlock(&forks[fork_i].fork_lock);
		return (-1);
	}
	printf("%lld %d has taken a fork\n", philo->temp_time / 1000, philo->philo_id);
	forks[fork_i].fork = 0;
	pthread_mutex_unlock(&philo->info->print_lock);
	return (0);
}

int	take_forks(t_philo *philo, t_forks *forks)
{
	if (philo->philo_id % 2 == 0)
	{
		if (take_fork(philo, forks, philo->left) == -1)
			return (-1);
		if (take_fork(philo, forks, philo->right) == -1)
			return (-1);
	}
	else
	{
		if (take_fork(philo, forks, philo->right) == -1)
			return (-1);
		if (take_fork(philo, forks, philo->left) == -1)
			return (-1);
	}
	return (0);
}


