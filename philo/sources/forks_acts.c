/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:18:25 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/21 12:48:52 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	put_forks(t_philo *philo, t_forks *forks)
{
	pthread_mutex_lock(&forks[philo->right].fork_lock);
	pthread_mutex_lock(&philo->info->print_lock);
	if (philo->info->death != 1)
		printf("%lld %d has put down a fork\n",
			get_msec(&philo->tv), philo->philo_id);
	pthread_mutex_unlock(&philo->info->print_lock);
	philo->forks[philo->right].fork = 1;
	pthread_mutex_unlock(&forks[philo->right].fork_lock);
	pthread_mutex_lock(&forks[philo->left].fork_lock);
	pthread_mutex_lock(&philo->info->print_lock);
	if (philo->info->death != 1)
		printf("%lld %d has put down a fork\n",
			get_msec(&philo->tv), philo->philo_id);
	pthread_mutex_unlock(&philo->info->print_lock);
	philo->forks[philo->left].fork = 1;
	pthread_mutex_unlock(&forks[philo->left].fork_lock);
	return (0);
}

int	take_both(t_philo *philo, t_forks *forks)
{
	pthread_mutex_lock(&forks[philo->left].fork_lock);
	pthread_mutex_lock(&philo->info->print_lock);
	if (philo->info->death != 1)
		printf("%lld %d has taken a fork\n",
			get_msec(&philo->tv), philo->philo_id);
	pthread_mutex_unlock(&philo->info->print_lock);
	forks[philo->left].fork = 0;
	forks[philo->left].queue = 0;
	pthread_mutex_unlock(&forks[philo->left].fork_lock);
	pthread_mutex_lock(&forks[philo->right].fork_lock);
	pthread_mutex_lock(&philo->info->print_lock);
	if (philo->info->death != 1)
		printf("%lld %d has taken a fork\n",
			get_msec(&philo->tv), philo->philo_id);
	pthread_mutex_unlock(&philo->info->print_lock);
	forks[philo->right].fork = 0;
	forks[philo->right].queue = 0;
	pthread_mutex_unlock(&forks[philo->right].fork_lock);
	return (0);
}

int	check_fork(t_philo *philo, t_forks *forks, int fork_i, int res)
{
	pthread_mutex_lock(&forks[fork_i].fork_lock);
	if (forks[fork_i].queue == philo->philo_id || forks[fork_i].queue == 0)
	{
		if (forks[fork_i].fork == 0)
			forks[fork_i].queue = philo->philo_id;
		if (forks[fork_i].fork == 1 && res == 1)
		{
			pthread_mutex_unlock(&forks[fork_i].fork_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&forks[fork_i].fork_lock);
	return (0);
}

int	chck_wait_fork(t_philo *philo, t_forks *forks, int first, int second)
{
	while (1)
	{
		philo->res = check_fork(philo, forks, first, 1);
		philo->res += check_fork(philo, forks, second, philo->res);
		if (philo->res == 2)
		{
			if (take_both(philo, forks) == -1)
				return (-1);
			return (1);
		}
		usleep(50);
		if (is_dead(philo, philo->info) == -1)
			return (-1);
		pthread_mutex_unlock(&philo->info->print_lock);
	}
	return (1);
}

int	take_forks(t_philo *philo, t_forks *forks)
{
	if (philo->philo_id % 2 == 0)
	{
		if (chck_wait_fork(philo, forks, philo->right, philo->left) == -1)
			return (-1);
	}
	else
	{
		usleep(200);
		if (chck_wait_fork(philo, forks, philo->left, philo->right) == -1)
			return (-1);
	}
	return (0);
}
