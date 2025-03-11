/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:43:03 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/12 00:09:14 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	die(t_philo *philo)
{
	printf("%lld %d died\n", cur_time(), philo->philo_id);
	return (0);
}

int	go_sleep(t_philo *philo)
{
	printf("%lld %d is sleeping\n", cur_time(), philo->philo_id);
	usleep(philo->info->slp_time);
	return (0);
}

int	go_think(t_philo *philo, int hungry_time)
{
	long long time;

	printf("%lld %d is thinking\n", cur_time(), philo->philo_id);
	time = philo->info->dth_time - cur_time() - hungry_time;
	if (time < 0)
		time = 0;
	usleep(time); // FIX, must die
	return (0);
}

int	go_eat(t_philo *philo)
{
	printf("%lld %d is eating\n", cur_time(), philo->philo_id);
	usleep(philo->info->eat_time);
	return (0);
}

void	*routine(void *new)
{
	int			my_meals;
	long long	hungry_time;
	t_philo *philo = (t_philo *)new;

	//printf("live\n"); del
	my_meals = philo->info->meals;
	hungry_time = cur_time();
	while (philo->info->stop_flag == 0 || my_meals > 0)
	{
		if (take_forks(philo) == -1)
			return (0);
		if (go_eat(philo) == -1)
			return (0);
		if (put_forks(philo) == -1)
			return (0);
		my_meals--;
		if (go_sleep(philo) == -1)
			return (0);
		if (go_think(philo, hungry_time) == -1)
			return (0);
	}
	return (0);
}
