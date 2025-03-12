/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:18:25 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/12 20:39:59 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



// int	chck_grap_fork(t_forks *forks, int fork_i, t_philo *philo)
// {
// 	int	res;

// 	res = 0;
// 	pthread_mutex_lock(&forks[fork_i].lock);
// 	if (forks[fork_i].fork == 1)
// 	{
// 		forks[fork_i].fork = 0;
// 		res = 1;
// 		printf("%lld %d has taken a fork\n", cur_time(&philo->tv), philo->philo_id);
// 	}
// 	else
// 		res = 0;
// 	pthread_mutex_unlock(&forks[fork_i].lock);
// 	return (res);
// }

// // is_time_to_die?
// int	take_forks(t_philo *philo)
// {
// 	if (philo->philo_id % 2 == 0)
// 	{
// 		while (chck_grap_fork(philo->forks, philo->left, philo) != 1)
// 			if (!usleep(1000) && is_died(philo) == -1)
// 				return (-1);
// 		while (chck_grap_fork(philo->forks, philo->right, philo) != 1)
// 			if (!usleep(1000) && is_died(philo) == -1)
// 				return (-1);
// 	}
// 	else
// 	{
// 		while (chck_grap_fork(philo->forks, philo->right, philo) != 1)
// 			if (!usleep(1000) && is_died(philo) == -1)
// 				return (-1);
// 		while (chck_grap_fork(philo->forks, philo->left, philo) != 1)
// 			if (!usleep(1000) && is_died(philo) == -1)
// 				return (-1);
// 	}
// 	return (0);
// }

int	put_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->left].lock);
	pthread_mutex_lock(&philo->forks[philo->right].lock);
	philo->temp_time = cur_time(&philo->tv);
	philo->forks[philo->left].fork = 1;
	printf("%lld %d put a fork down\n", philo->temp_time, philo->philo_id);
	philo->forks[philo->right].fork = 1;
	printf("%lld %d put a fork down\n", philo->temp_time, philo->philo_id);
	pthread_mutex_unlock(&philo->forks[philo->right].lock);
	pthread_mutex_unlock(&philo->forks[philo->left].lock);
	if (is_died(philo) == -1)
		return (-1);
	return (0);
}

int	take_forks(t_philo *philo)
{
	while (philo->left == philo->right)
		if (is_died(philo) == -1)
			return (-1);
	if (philo->philo_id % 2 == 0)
	{
		while (1)
		{
			if (!usleep(1000) && is_died(philo) == -1)
				return (-1);
			if (chck_grap_fork(philo, philo->forks) == 1)
				return (0);
		}
	}
	else
	{
		while (1)
		{
			while (!usleep(1000) && is_died(philo) == -1)
				return (-1);
			if (chck_grap_fork(philo, philo->forks) == 1)
				return (0);
		}
	}
	return (0);
}

int	chck_grap_fork(t_philo *philo, t_forks *forks)
{
	int	res;

	res = 0;
	//printf("Philo %d lock left fork\n", philo->philo_id); DEL
	pthread_mutex_lock(&forks[philo->left].lock);
	//printf("Philo %d lock right fork\n", philo->philo_id); DEL
	pthread_mutex_lock(&forks[philo->right].lock);
	// if (forks[philo->left].fork == 1)
	// {
	// 	printf("%lld %d has taken a fork\n", cur_time(&philo->tv), philo->philo_id);
	// }

	//printf("%lld Philo %d try \n", cur_time(&philo->tv), philo->philo_id); // DEL
	if (forks[philo->right].fork == 1 && forks[philo->left].fork == 1)
	{
		forks[philo->left].fork = 0;
		forks[philo->right].fork = 0;
		philo->temp_time = cur_time(&philo->tv);
		printf("%lld %d has taken a fork\n", philo->temp_time, philo->philo_id);
		printf("%lld %d has taken a fork\n", philo->temp_time, philo->philo_id);
		res = 1;
	}
	// else
	// {
	// 	//printf("%lld %d put a fork down\n", cur_time(&philo->tv), philo->philo_id);
	// }
	//printf("Philo %d unlock left fork\n", philo->philo_id); DEL
	pthread_mutex_unlock(&forks[philo->left].lock);
	//printf("Philo %d unlock right fork\n", philo->philo_id);
	pthread_mutex_unlock(&forks[philo->right].lock);
	return (res);
}
