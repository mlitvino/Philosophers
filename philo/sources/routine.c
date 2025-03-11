/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:43:03 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/11 19:43:23 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_sleep(t_philo *philo)
{

}

void	go_think(t_philo *philo, int hungry_time)
{
	int	time;
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

void	put_forks(t_philo *philo)
{

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

int	routine(t_philo *philo)
{
	int		my_meals;
	int		hungry_time;
	struct	timeval time;

	my_meals = philo->info->meals;
	while (philo->info->stop_flag == 0 || my_meals > 0)
	{
		gettimeofday(&time, NULL);
		hungry_time = time.tv_usec;
		take_forks(philo, time);
		go_eat(philo);
		put_forks(philo);
		go_sleep(philo);
		go_think(philo, hungry_time);
	}
	return (0);
}
