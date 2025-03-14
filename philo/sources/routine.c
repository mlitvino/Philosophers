/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:43:03 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/14 17:05:26 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	go_sleep(t_philo *philo, t_info *info)
{
	if (is_dead(philo, info) == -1)
		return (-1);
	printf("%lld %d is sleeping\n", philo->temp_time / 1000, philo->philo_id);
	pthread_mutex_unlock(&info->print_lock);
	philo->temp_time = philo->dth_date - philo->temp_time - info->slp_time;
	if (philo->temp_time >= 0)
		usleep(info->slp_time);
	else
		usleep(info->slp_time + philo->temp_time);
	return (0);
}

int	go_think(t_philo *philo, t_info *info)
{
	if (is_dead(philo, info) == -1)
		return (-1);
	printf("%lld %d is thinking\n", philo->temp_time / 1000, philo->philo_id);
	pthread_mutex_unlock(&info->print_lock);
	// gettimeofday(&philo->time, NULL);
	// philo->eat_date = (philo->time.tv_sec * 1000) + (philo->time.tv_usec / 1000);
	// philo->eat_date = philo->dth_date - philo->eat_date + 15;
	// if (philo->eat_date >= 0)
		usleep(1000);
	// else
	// 	usleep(-philo->eat_date);
	return (0);
}

int	is_dead(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&info->print_lock);
	philo->temp_time = get_usec(&philo->tv);
	if (philo->temp_time >= philo->dth_date || info->death == 1)
	{
		info->death = 1;
		printf("%lld %d died\n", philo->temp_time / 1000, philo->philo_id);
		pthread_mutex_unlock(&info->print_lock);
		return (-1);
	}
	return (0);
}

int	go_eat(t_philo *philo, t_info *info)
{
	if (is_dead(philo, info) == -1)
		return (-1);
	printf("%lld %d is eating\n", philo->temp_time / 1000, philo->philo_id);
	pthread_mutex_unlock(&info->print_lock);
	usleep(info->eat_time);
	philo->dth_date = philo->temp_time + info->dth_time;
	return (0);
}

void	*routine(void *new)
{
	int			my_meals;
	t_philo		*philo;

	philo = (t_philo *)new;
	my_meals = philo->info->meals;
	philo->temp_time = get_usec(&philo->tv);
	philo->dth_date = philo->temp_time + philo->info->dth_time;
	while (philo->info->stop_flag == 0 || my_meals-- > 0)
	{
		if (go_sleep(philo, philo->info) == -1)
			return (0);
		if (go_think(philo, philo->info) == -1)
			return (0);
		if (take_forks(philo, philo->forks) == -1)
			return (0);
		if (go_eat(philo, philo->info) == -1)
			return (0);
		if (put_forks(philo) == -1)
			return (0);
	}
	printf("%lld %d has done\n", get_msec(&philo->tv), philo->philo_id);
	return (0);
}
