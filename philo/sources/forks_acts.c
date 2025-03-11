/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:18:25 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/12 00:07:55 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	put_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->left].lock);
	philo->forks[philo->left].fork = 1;
	pthread_mutex_unlock(&philo->forks[philo->left].lock);
	printf("%lld %d put a fork down\n", cur_time(), philo->philo_id);
	pthread_mutex_lock(&philo->forks[philo->right].lock);
	philo->forks[philo->right].fork = 1;
	pthread_mutex_unlock(&philo->forks[philo->right].lock);
	printf("%lld %d put a fork down\n", cur_time(), philo->philo_id);
	return (0);
}

int	take_fork(t_forks *forks, int fork_i, t_philo *philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&forks[fork_i].lock);
	if (forks[fork_i].fork == 1)
	{
		forks[fork_i].fork = 0;
		res = 1;
		printf("%lld %d has taken a fork\n", cur_time(), philo->philo_id);
	}
	else
		res = 0;
	pthread_mutex_unlock(&forks[fork_i].lock);
	return (res);
}

// is_time_to_die?
int	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		while (take_fork(philo->forks, philo->left, philo) != 1)
			usleep(5);
		while (take_fork(philo->forks, philo->right, philo) != 1)
			usleep(5);
	}
	else
	{
		while (take_fork(philo->forks, philo->right, philo) != 1)
			usleep(5);
		while (take_fork(philo->forks, philo->left, philo) != 1)
			usleep(5);
	}
	return (0);
}
