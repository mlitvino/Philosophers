/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:01:52 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/19 23:24:15 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	delete_old_sem()
{
	sem_unlink("/forks_sem");
	sem_unlink("/lock_sem");
	sem_unlink("/print_sem");
	sem_unlink("/globl_dth_sem");
	sem_unlink("/chk_fork_sem");
}

void	init_sem(t_my_sem *forks, t_info *info)
{
	delete_old_sem();
	forks->forks = sem_open("/forks_sem", O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR | S_IXUSR, info->max_philos);
	forks->lock = sem_open("/lock_sem", O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR | S_IXUSR, 1);
	forks->print = sem_open("/print_sem", O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR | S_IXUSR, 1);
	forks->globl_dth = sem_open("/globl_dth_sem", O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR | S_IXUSR, 0);
	forks->chk_fork = sem_open("/chk_fork_sem", O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR | S_IXUSR, 1);
	if (forks->forks == SEM_FAILED || forks->lock == SEM_FAILED
		|| forks->print == SEM_FAILED || forks->globl_dth == SEM_FAILED
		|| forks->chk_fork == SEM_FAILED)
	{
		clean_sem(forks);
		error("Error: semaphore creation failed");
	}
}

int	create_philos(t_philo *philos, t_info *info, t_my_sem *forks)
{
	int		i;
	pid_t	pid;

	i = 0;
	philos->forks = forks;
	philos->info = info;
	philos->globl_death = 0;
	philos->taken_fork = 0;
	while (i < info->max_philos)
	{
		pid = fork();
		if (pid == -1)
		{
			sem_post(forks->globl_dth);
			while (waitpid(0, 0, 0) != -1)
				usleep(100);
			clean_sem(forks);
			error("Error: fork failed child creation");
		}
		else if (pid == 0)
			routine(philos, info, forks, i + 1);
		i++;
	}
	return (0);
}
