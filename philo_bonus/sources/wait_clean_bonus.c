/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_clean_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:34:11 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/23 20:56:50 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*wait_death(void *new_philo)
{
	t_philo	*philo;

	philo = (t_philo *)new_philo;
	sem_wait(philo->forks->globl_dth);
	philo->globl_death = 1;
	sem_post(philo->forks->globl_dth);
	return (0);
}

void	proc_exit_clean(t_my_sem *forks, t_philo *philo)
{
	pthread_join(philo->wait_dth_thrd, NULL);
	sem_close(forks->globl_dth);
	sem_close(forks->forks);
	sem_close(forks->lock);
	sem_close(forks->print);
	sem_close(forks->chk_fork);
}

void	clean_sem(t_my_sem *forks)
{
	sem_close(forks->forks);
	sem_close(forks->lock);
	sem_close(forks->print);
	sem_close(forks->globl_dth);
	sem_close(forks->chk_fork);
	if (forks->forks != SEM_FAILED)
		sem_unlink("/forks_sem");
	if (forks->lock != SEM_FAILED)
		sem_unlink("/lock_sem");
	if (forks->print != SEM_FAILED)
		sem_unlink("/print_sem");
	if (forks->globl_dth != SEM_FAILED)
		sem_unlink("/globl_dth_sem");
	if (forks->chk_fork != SEM_FAILED)
		sem_unlink("/chk_fork_sem");
}

void	wait_clean(t_my_sem *forks)
{
	int	status;
	int	res;

	res = 0;
	while (res != -1)
	{
		res = waitpid(0, &status, 0);
		if (res != -1 && WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			sem_wait(forks->globl_dth);
			sem_post(forks->globl_dth);
			sem_post(forks->print);
		}
	}
	clean_sem(forks);
}
