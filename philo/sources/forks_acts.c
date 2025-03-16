/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:18:25 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/16 15:51:41 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	put_forks(t_philo *philo)
// {
// 	philo->forks[philo->right].fork = 1;
// 	if (is_dead(philo, philo->info) == -1)
// 	{
// 		pthread_mutex_unlock(&forks[philo->left].fork_lock);
// 		pthread_mutex_unlock(&forks[philo->right].fork_lock);
// 		return (-1);
// 	}
// 	printf("%lld %d put a fork down\n", philo->temp_time / 1000, philo->philo_id);
// 	pthread_mutex_unlock(&info->print_lock);
// 	pthread_mutex_unlock(&forks[philo->right].fork_lock);
// 	philo->forks[philo->left].fork = 1;
// 	if (is_dead(philo, philo->info) == -1)
// 	{
// 		pthread_mutex_unlock(&forks[philo->left].fork_lock);
// 		return (-1);
// 	}
// 	printf("%lld %d put a fork down\n", philo->temp_time / 1000, philo->philo_id);
// 	pthread_mutex_unlock(&info->print_lock);
// 	pthread_mutex_unlock(&forks[philo->left].fork_lock);
// 	return (0);
// }

// int	take_fork(t_philo *philo, t_forks *forks, int fork_i)
// {
// 	pthread_mutex_lock(&forks[fork_i].fork_lock);
// 	if (is_dead(philo, philo->info) == -1)
// 	{
// 		pthread_mutex_unlock(&forks[fork_i].fork_lock);
// 		return (-1);
// 	}
// 	printf("%lld %d has taken a fork\n", philo->temp_time / 1000, philo->philo_id);
// 	forks[fork_i].fork = 0;
// 	pthread_mutex_unlock(&info->print_lock);
// 	return (0);
// }

// int	take_forks(t_philo *philo, t_forks *forks)
// {
// 	if (philo->philo_id % 2 == 0)
// 	{
// 		if (take_fork(philo, forks, philo->left) == -1)
// 			return (-1);
// 		if (take_fork(philo, forks, philo->right) == -1)
// 		{
// 			pthread_mutex_unlock(&forks[philo->left].fork_lock);
// 			return (-1);
// 		}
// 	}
// 	else
// 	{
// 		if (take_fork(philo, forks, philo->right) != -1)
// 			return (-1);
// 		if (take_fork(philo, forks, philo->left) != -1)
// 		{
// 			pthread_mutex_unlock(&forks[philo->right].fork_lock);
// 			return (-1);
// 		}
// 	}
// 	return (0);
// }

int	put_forks(t_philo *philo, t_forks *forks, t_info *info)
{
	pthread_mutex_lock(&forks[philo->right].fork_lock);
	if (is_dead(philo, philo->info) == -1)
	{
		pthread_mutex_unlock(&forks[philo->right].fork_lock);
		return (-1);
	}
	printf("%lld %d put a fork down\n",
		philo->temp_time / 1000, philo->philo_id);
	pthread_mutex_unlock(&info->print_lock);
	philo->forks[philo->right].fork = 1;
	pthread_mutex_unlock(&forks[philo->right].fork_lock);




	pthread_mutex_lock(&forks[philo->left].fork_lock);
	if (is_dead(philo, philo->info) == -1)
	{
		pthread_mutex_unlock(&forks[philo->left].fork_lock);
		return (-1);
	}
	printf("%lld %d put a fork down\n",
		philo->temp_time / 1000, philo->philo_id);
	pthread_mutex_unlock(&info->print_lock);
	philo->forks[philo->left].fork = 1;
	pthread_mutex_unlock(&forks[philo->left].fork_lock);
	return (0);
}

int	take_fork(t_philo *philo, t_forks *forks, int fork_i)
{
	pthread_mutex_lock(&forks[fork_i].fork_lock);
	if (forks[fork_i].queue == philo->philo_id || forks[fork_i].queue == 0)
	{
		if (forks[fork_i].fork == 0)
			forks[fork_i].queue = philo->philo_id;
		else
		{
			pthread_mutex_lock(&philo->info->print_lock);
			printf("%lld %d has taken a fork\n",
				get_usec(&philo->tv) / 1000, philo->philo_id);
			pthread_mutex_unlock(&philo->info->print_lock);
			forks[fork_i].fork = 0;
			forks[fork_i].queue = 0;
			pthread_mutex_unlock(&forks[fork_i].fork_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&forks[fork_i].fork_lock);
	return (0);
}

int	chck_wait_fork(t_philo *philo, t_forks *forks, int fork_i)
{
	while (take_fork(philo, forks, fork_i) != 1)
	{
		usleep(1000);
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
		if (chck_wait_fork(philo, forks, philo->right) == -1)
			return (-1);
		if (chck_wait_fork(philo, forks, philo->left) == -1)
			return (-1);
	}
	else
	{
		if (chck_wait_fork(philo, forks, philo->left) == -1)
			return (-1);
		if (chck_wait_fork(philo, forks, philo->right) == -1)
			return (-1);
	}
	return (0);
}
