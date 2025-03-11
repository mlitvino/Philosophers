/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:43:03 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/11 20:33:56 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *philo)
{
	printf("%lld %d died\n", cur_time(), philo->philo_id);
}

void	go_sleep(t_philo *philo)
{
	printf("%lld %d is sleeping\n", cur_time(), philo->philo_id);
	usleep(philo->info->slp_time);
}

void	go_think(t_philo *philo, int hungry_time)
{
	printf("%lld %d is thinking\n", cur_time(), philo->philo_id);
	usleep(philo->info->slp_time); // FIX
}

void	go_eat(t_philo *philo)
{
	printf("%lld %d is eating\n", cur_time(), philo->philo_id);
	usleep(philo->info->eat_time);
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
