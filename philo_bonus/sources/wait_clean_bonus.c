/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_clean_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:34:11 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/17 17:51:43 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	err_clean(t_philo *philos, t_my_sem *forks, int mod)
{
	if (mod == 0)
	{
		sem_wait(forks->forks);
		usleep(philos->info->dth_time * 2);
		sem_post(forks->forks);
	}
	sem_close(forks->forks);
	sem_close(forks->lock);
	sem_close(forks->print);
	sem_close(forks->globl_dth);
	sem_unlink("/forks_sem");
	sem_unlink("/lock_sem");
	sem_unlink("/print_sem");
	sem_unlink("/globl_dth_sem");
}

// void	wait_clean(t_philo *philos, t_my_sem *forks, int max_philos)
// {
// 	int	i;
// 	int	status;
// 	int	res;

// 	i = 0;
// 	while (i < max_philos)
// 	{
// 		res = waitpid(0, &status, 0);
// 		if (res != -1 && WIFEXITED(status) && WEXITSTATUS(status) == 1)
// 		{
// 			usleep(philos->info->dth_time * 2);
// 			sem_post(forks->print);
// 		}
// 		i++;
// 	}
// 	err_clean(philos, forks, 1);
// }

void	wait_clean(t_philo *philos, t_my_sem *forks)
{
	int	i;
	int	status;
	int	res;

	i = 0;
	res = 0;
	while (res != -1)
	{
		res = waitpid(0, &status, 0);
		if (res != -1 && WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			sem_post(forks->globl_dth);
			sem_wait(forks->globl_dth);
			sem_post(forks->print);
		}
	}
	err_clean(philos, forks, 1);
}
