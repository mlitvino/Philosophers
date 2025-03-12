/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:43:03 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/12 20:31:31 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	go_sleep(t_philo *philo)
{
	if (is_died(philo) == -1)
		return (-1);
	philo->eat_date = cur_time(&philo->tv);
	printf("%lld %d is sleeping\n", philo->eat_date, philo->philo_id);
	philo->eat_date = philo->dth_date - philo->eat_date - philo->info->slp_time;
	//printf("eat %lld\n", philo->eat_date);//del
	if (philo->eat_date >= 0)
		usleep(philo->info->slp_time * 1000);
	else
		usleep((philo->info->slp_time + philo->eat_date) * 1000);
	return (0);
}

int	go_think(t_philo *philo)
{
	if (is_died(philo) == -1)
		return (-1);
	printf("%lld %d is thinking\n", cur_time(&philo->tv), philo->philo_id);
	// gettimeofday(&philo->time, NULL);
	// philo->eat_date = (philo->time.tv_sec * 1000) + (philo->time.tv_usec / 1000);
	// philo->eat_date = philo->dth_date - philo->eat_date + 15;
	// if (philo->eat_date >= 0)
		usleep(1000);
	// else
	// 	usleep(-philo->eat_date);
	return (0);
}

int	is_died(t_philo *philo)
{
	philo->temp_time = cur_time(&philo->tv);
	//printf("time %lld date %lld\n", philo->temp_time, philo->dth_date); DEL
	if (philo->temp_time >= philo->dth_date)
	{
		printf("%lld %d died\n", philo->temp_time, philo->philo_id);
		return (-1);
	}
	return (0);
}

int	go_eat(t_philo *philo, t_info *info)
{
	if (is_died(philo) == -1)
		return (-1);
	philo->eat_date = cur_time(&philo->tv);
	printf("%lld %d is eating\n", philo->eat_date, philo->philo_id);
	usleep(info->eat_time * 1000);
	philo->dth_date = philo->eat_date + info->dth_time;
	return (0);
}

void	*routine(void *new)
{
	int			my_meals;
	t_philo		*philo;

	philo = (t_philo *)new;
	my_meals = philo->info->meals;
	philo->eat_date = cur_time(&philo->tv);
	philo->dth_date = philo->eat_date + philo->info->dth_time;
	//printf("%lld %d start\n", philo->eat_date, philo->philo_id);
	//printf("%lld %d death\n", philo->dth_date, philo->philo_id);
	//printf("%lld date\n", philo->dth_date);//dEL
	while (philo->info->stop_flag == 0 || my_meals-- > 0)
	{
		if (go_sleep(philo) == -1)
			return (0);
		// if (go_think(philo) == -1)
		// 	return (0);
		if (take_forks(philo) == -1)
			return (0);
		if (go_eat(philo, philo->info) == -1)
			return (0);
		if (put_forks(philo) == -1)
			return (0);
		//printf("\nmeals %d\n\n", my_meals); //DEL
	}
	printf("%lld %d has done\n", cur_time(&philo->tv), philo->philo_id);
	return (0);
}
