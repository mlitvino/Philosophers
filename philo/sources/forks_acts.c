/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:18:25 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/11 20:25:11 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->left].lock);
	philo->forks[philo->left].fork = 1;
	pthread_mutex_unlock(&philo->forks[philo->left].lock);
	// print?
	pthread_mutex_lock(&philo->forks[philo->right].lock);
	philo->forks[philo->right].fork = 1;
	pthread_mutex_unlock(&philo->forks[philo->right].lock);
	// print?
}

int	take_fork(t_forks *forks, int fork_i)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&forks[fork_i].lock);
	if (forks[fork_i].fork == 1)
	{
		forks[fork_i].fork == 0;
		res = 1;
	}
	else
		res = 0;
	pthread_mutex_unlock(&forks[fork_i].lock);
	return (res);
}

// is_time_to_die?
void	take_forks(t_philo *philo, struct timeval time)
{
	int ph_n;

	ph_n = philo->philo_id + 1;
	if (ph_n % 2 == 0)
	{
		while (take_fork(philo->forks, philo->left) != 1)
			usleep(5);
		gettimeofday(&time, NULL);
		printf("%d %d has taken a fork\n", time.tv_usec / 1000, ph_n);
		while (take_fork(philo->forks, philo->right) != 1)
			usleep(5);
		gettimeofday(&time, NULL);
		printf("%d %d has taken a fork\n", time.tv_usec / 1000, ph_n);
	}
	else
	{
		while (take_fork(philo->forks, philo->right) != 1)
			usleep(5);
		gettimeofday(&time, NULL);
		printf("%d %d has taken a fork\n", time.tv_usec / 1000, ph_n);
		while (take_fork(philo->forks, philo->left) != 1)
			usleep(5);
		gettimeofday(&time, NULL);
		printf("%d %d has taken a fork\n", time.tv_usec / 1000, ph_n);
	}
}
