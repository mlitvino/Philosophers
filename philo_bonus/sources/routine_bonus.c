/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:43:03 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/19 17:57:35 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	go_sleep(t_philo *philo, t_info *info)
{
	if (is_dead(philo, philo->forks) == -1)
	{
		proc_exit_clean(philo->forks, philo);
		exit(1);
	}
	printf("%lld %d is sleeping\n", get_msec(&philo->tv), philo->philo_i);
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
	if (is_dead(philo, philo->forks) == -1)
	{
		proc_exit_clean(philo->forks, philo);
		exit(1);
	}
	printf("%lld %d is thinking\n", get_msec(&philo->tv), philo->philo_i);
	sem_post(philo->forks->print);
	return (0);
}

int	is_dead(t_philo *philo, t_my_sem *forks)
{
	sem_wait(forks->print);
	philo->temp_time = get_usec(&philo->tv);
	if (philo->temp_time >= philo->dth_date || philo->globl_death == 1)
	{
		if (philo->globl_death == 1)
			return (-1);
		sem_post(forks->globl_dth);
		printf("%lld %d died\n", get_msec(&philo->tv), philo->philo_i);
		return (-1);
	}
	return (0);
}

int	go_eat(t_philo *philo, t_info *info, t_my_sem *forks)
{
	if (is_dead(philo, forks) == -1)
	{
		proc_exit_clean(philo->forks, philo);
		exit(1);
	}
	printf("%lld %d is eating\n", get_msec(&philo->tv), philo->philo_i);
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
	philo->philo_i = philo_i;
	if (pthread_create(&philo->wait_dth_thrd, NULL,
			wait_death, (void *)philo) != 0)
	{
		sem_wait(forks->print);
		sem_post(forks->globl_dth);
		proc_exit_clean(forks, philo);
		error("Error: thread creation failed");
	}
	philo->dth_date = get_usec(&philo->tv) + info->dth_time;
	while (info->stop_flag == 0 || info->meals-- > 0)
	{
		take_forks(philo, forks);
		go_eat(philo, info, forks);
		put_forks(philo, forks);
		go_sleep(philo, info);
		go_think(philo);
	}
	usleep(info->eat_time * 2);
	sem_post(forks->globl_dth);
	proc_exit_clean(forks, philo);
	exit(0);
}
