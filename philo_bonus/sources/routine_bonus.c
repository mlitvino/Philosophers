/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:43:03 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/17 00:30:59 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	go_sleep(t_philo *philo, t_info *info)
{
	is_dead(philo, 0);
	printf("%lld %d is sleeping\n", philo->temp_time / 1000, philo->philo_i);
	sem_post(philo->forks->print);
	philo->temp_time = philo->dth_date - philo->temp_time - info->slp_time;
	if (philo->temp_time >= 0)
		usleep(info->slp_time);
	else
		usleep(info->slp_time + philo->temp_time);
	return (0);
}

int	go_think(t_philo *philo)
{
	is_dead(philo, 0);
	printf("%lld %d is thinking\n", philo->temp_time / 1000, philo->philo_i);
	sem_post(philo->forks->print);
	return (0);
}

int	is_dead(t_philo *philo, int mod)
{
	philo->check_time = get_usec(&philo->tv);
	sem_wait(philo->forks->print);
	philo->temp_time = get_usec(&philo->tv);
	if (philo->temp_time >= philo->dth_date)
	{
		if (mod == 1)
		{
			sem_post(philo->forks->forks);
			sem_post(philo->forks->forks);
		}
		sem_close(philo->forks->forks);
		sem_close(philo->forks->lock);
		sem_close(philo->forks->print);
		if (philo->temp_time - philo->check_time >= philo->info->dth_time)
			exit(0);
		printf("%lld %d died\n", philo->temp_time / 1000, philo->philo_i);
		exit(1);
	}
	return (0);
}

int	go_eat(t_philo *philo, t_info *info, t_my_sem *forks)
{
	is_dead(philo, 1);
	printf("%lld %d is eating\n", philo->temp_time / 1000, philo->philo_i);
	sem_post(forks->print);
	if (info->eat_time >= info->dth_time)
		usleep(info->dth_time);
	else
	{
		philo->dth_date = philo->temp_time + info->dth_time;
		usleep(info->eat_time);
	}
	return (0);
}

int	routine(t_philo *philo, t_info *info, t_my_sem *forks, int philo_i)
{
	int	my_meals;

	my_meals = info->meals;
	philo->philo_i = philo_i;
	philo->dth_date = get_usec(&philo->tv) + info->dth_time;
	while (info->max_philos == 1)
		is_dead(philo, 0);
	while (info->stop_flag == 0 || my_meals-- > 0)
	{
		take_forks(philo, forks);
		go_eat(philo, info, forks);
		put_forks(philo, forks);
		go_sleep(philo, info);
		go_think(philo);
	}
	printf("%lld %d has done\n", get_msec(&philo->tv), philo->philo_i);
	sem_close(forks->forks);
	sem_close(forks->lock);
	sem_close(forks->print);
	exit(0);
}
