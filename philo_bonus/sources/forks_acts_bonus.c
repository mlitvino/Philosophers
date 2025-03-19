/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_acts_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:18:25 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/19 17:59:07 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*wait_fork_thrd(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	sem_wait(philo->forks->forks);
	sem_wait(philo->forks->chk_fork);
	philo->taken_fork = 1;
	sem_post(philo->forks->chk_fork);
	return (0);
}

int	put_forks(t_philo *philo, t_my_sem *forks)
{
	if (is_dead(philo, forks) == -1)
	{
		proc_exit_clean(philo->forks, philo);
		exit(1);
	}
	sem_post(forks->forks);
	printf("%lld %d put a fork down\n", get_msec(&philo->tv), philo->philo_i);
	sem_post(forks->forks);
	printf("%lld %d put a fork down\n", get_msec(&philo->tv), philo->philo_i);
	sem_post(forks->print);
	return (0);
}

void	create_wait_thread(t_philo *philo, t_my_sem *forks)
{
	if (pthread_create(&philo->wait_fork_thrd,
			NULL, wait_fork_thrd, (void *)philo) != 0)
	{
		sem_wait(forks->print);
		sem_post(forks->lock);
		sem_post(forks->globl_dth);
		sem_wait(forks->globl_dth);
		proc_exit_clean(forks, philo);
		printf("Error: thread creation failed\n");
		exit(1);
	}
}

void	take_fork(t_philo *philo, t_my_sem *forks)
{
	create_wait_thread(philo, forks);
	while (1)
	{
		sem_wait(philo->forks->chk_fork);
		if (philo->taken_fork != 0)
			break ;
		sem_post(philo->forks->chk_fork);
		if (is_dead(philo, forks) == -1)
		{
			sem_post(forks->forks);
			sem_post(forks->lock);
			pthread_join(philo->wait_fork_thrd, NULL);
			proc_exit_clean(forks, philo);
			exit(1);
		}
		sem_post(forks->print);
		usleep(250);
	}
	pthread_detach(philo->wait_fork_thrd);
	sem_post(philo->forks->chk_fork);
}

int	take_forks(t_philo *philo, t_my_sem *forks)
{
	sem_wait(forks->lock);
	take_fork(philo, forks);
	philo->taken_fork = 0;
	sem_wait(forks->print);
	if (philo->globl_death == 1)
		return (sem_post(forks->print), 0);
	printf("%lld %d has taken a fork\n", get_msec(&philo->tv), philo->philo_i);
	sem_post(forks->print);
	take_fork(philo, forks);
	philo->taken_fork = 0;
	sem_wait(forks->print);
	if (philo->globl_death == 1)
		return (sem_post(forks->print), 0);
	printf("%lld %d has taken a fork\n", get_msec(&philo->tv), philo->philo_i);
	sem_post(forks->print);
	sem_post(forks->lock);
	return (0);
}
