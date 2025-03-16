/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_acts_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:18:25 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/17 00:29:36 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	put_forks(t_philo *philo, t_my_sem *forks)
{
	is_dead(philo, 1);
	sem_post(forks->forks);
	sem_post(forks->forks);
	printf("%lld %d put a fork down\n", philo->temp_time / 1000, philo->philo_i);
	printf("%lld %d put a fork down\n", philo->temp_time / 1000, philo->philo_i);
	sem_post(forks->print);
	return (0);
}

int	take_forks(t_philo *philo, t_my_sem *forks)
{
	is_dead(philo, 0);
	sem_post(forks->print);
	sem_wait(forks->lock);
	sem_wait(forks->forks);
	sem_wait(forks->print);
	printf("%lld %d has taken a fork\n", philo->temp_time / 1000, philo->philo_i);
	sem_post(forks->print);
	sem_wait(forks->forks);
	sem_wait(forks->print);
	printf("%lld %d has taken a fork\n", philo->temp_time / 1000, philo->philo_i);
	sem_post(forks->print);
	sem_post(forks->lock);
	return (0);
}
