/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_acts_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:18:25 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/13 23:22:53 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
			if (chck_grap_fork(philo, forks, philo->left, philo->right) == 1)
				return (0);
*/

// int	chck_grap_fork(t_philo *philo, t_my_sem *forks, int first, int second)
// {
// 	int	res;

// 	res = 0;
// 	//printf("Philo %d lock left fork\n", philo->philo_i); DEL
// 	pthread_mutex_lock(&forks[philo->left].lock);
// 	//printf("Philo %d lock right fork\n", philo->philo_i); DEL
// 	pthread_mutex_lock(&forks[philo->right].lock);
// 	// if (forks[philo->left].fork == 1)
// 	// {
// 	// 	printf("%lld %d has taken a fork\n", cur_time(&philo->tv), philo->philo_i);
// 	// }

// 	//printf("%lld Philo %d try \n", cur_time(&philo->tv), philo->philo_i); // DEL
// 	if (forks[philo->right].fork == 1 && forks[philo->left].fork == 1)
// 	{
// 		forks[philo->left].fork = 0;
// 		forks[philo->right].fork = 0;
// 		philo->temp_time = cur_time(&philo->tv);
// 		printf("%lld %d has taken a fork\n", philo->temp_time, philo->philo_i);
// 		printf("%lld %d has taken a fork\n", philo->temp_time, philo->philo_i);
// 		res = 1;
// 	}
// 	// else
// 	// {
// 	// 	//printf("%lld %d put a fork down\n", cur_time(&philo->tv), philo->philo_i);
// 	// }
// 	//printf("Philo %d unlock left fork\n", philo->philo_i); DEL
// 	pthread_mutex_unlock(&forks[philo->left].lock);
// 	//printf("Philo %d unlock right fork\n", philo->philo_i);
// 	pthread_mutex_unlock(&forks[philo->right].lock);
// 	return (res);
// }

int	put_forks(t_philo *philo, t_my_sem *forks)
{
	sem_post(forks->forks);
	printf("%lld %d put a fork down\n", cur_time(&philo->tv), philo->philo_i);
	sem_post(forks->forks);
	printf("%lld %d put a fork down\n", cur_time(&philo->tv), philo->philo_i);
	is_dead(philo);
	return (0);
}

int	chck_grap_fork(t_philo *philo, t_my_sem *forks)
{
	//printf("graps\n"); //del
	sem_wait(forks->lock);
	//printf("grapsSSSS\n"); //del
	sem_wait(forks->forks);
	printf("%lld %d has taken a fork\n", cur_time(&philo->tv), philo->philo_i);
	sem_wait(forks->forks);
	printf("%lld %d has taken a fork\n", cur_time(&philo->tv), philo->philo_i);
	sem_post(forks->lock);
	//printf("sucsess\n"); //del
	return (1);
}

int	take_forks(t_philo *philo, t_my_sem *forks, t_info *info)
{
	while (info->max_philos == 1)
		is_dead(philo);
	if (philo->philo_i % 2 == 0)
	{
		while (1)
		{
			usleep(1000);
			is_dead(philo);
			if (chck_grap_fork(philo, forks) == 1)
				return (0);
		}
	}
	else
	{
		while (1)
		{
			usleep(1000);
			is_dead(philo);
			if (chck_grap_fork(philo, forks) == 1)
				return (0);
		}
	}
	return (0);
}
