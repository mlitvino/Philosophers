/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:43:03 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/13 23:50:14 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	go_sleep(t_philo *philo, t_info *info)
{
	is_dead(philo);
	philo->eat_date = cur_time(&philo->tv);
	printf("%lld %d is sleeping\n", philo->eat_date, philo->philo_i);
	philo->eat_date = philo->dth_date - philo->eat_date - info->slp_time;
	if (philo->eat_date >= 0)
		usleep(info->slp_time * 1000);
	else
		usleep((info->slp_time + philo->eat_date) * 1000);
	return (0);
}

int	go_think(t_philo *philo)
{
	is_dead(philo);
	printf("%lld %d is thinking\n", cur_time(&philo->tv), philo->philo_i);
	// gettimeofday(&philo->time, NULL);
	// philo->eat_date = (philo->time.tv_sec * 1000) + (philo->time.tv_usec / 1000);
	// philo->eat_date = philo->dth_date - philo->eat_date + 15;
	// if (philo->eat_date >= 0)
		usleep(1000);
	// else
	// 	usleep(-philo->eat_date);
	return (0);
}

int	is_dead(t_philo *philo)
{
	philo->temp_time = cur_time(&philo->tv);
	if (philo->temp_time >= philo->dth_date)
	{
		printf("%lld %d died\n", philo->temp_time, philo->philo_i);
		exit(1);
	}
	return (0);
}

int	go_eat(t_philo *philo, t_info *info)
{
	is_dead(philo);
	philo->eat_date = cur_time(&philo->tv);
	printf("%lld %d is eating\n", philo->eat_date, philo->philo_i);
	usleep(info->eat_time * 1000);
	philo->dth_date = philo->eat_date + info->dth_time;
	return (0);
}

int	routine(t_philo *philo, t_info *info, t_my_sem *forks)
{
	int	my_meals;

	my_meals = info->meals;
	philo->eat_date = cur_time(&philo->tv);
	philo->dth_date = philo->eat_date + info->dth_time;
	while (info->stop_flag == 0 || my_meals-- > 0)
	{
		go_sleep(philo, info);
		go_think(philo);
		take_forks(philo, forks, info);
		go_eat(philo, info);
		put_forks(philo, forks);
	}
	printf("%lld %d has done\n", cur_time(&philo->tv), philo->philo_i);
	sem_close(forks->forks);
	sem_close(forks->lock);
	free(philo->other);
	exit(0);
}
