/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_clean_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:34:11 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/13 23:35:47 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	err_clean(t_philo *philos, t_my_sem *forks, int max_philos)
{
	int	i;

	i = -1;
	while (++i < max_philos)
		if (philos[i].philo_pid != -1)
			kill(philos[i].philo_pid, SIGTERM);
	sem_close(forks->forks);
	sem_close(forks->lock);
	sem_unlink("/forks_sem");
	sem_unlink("/lock_sem");
	free(philos);
	philos = NULL;
}

void	wait_clean(t_philo *philos, t_my_sem *forks, int max_philos)
{
	int	i;

	i = 0;
	while (i < max_philos)
	{
		waitpid(philos[i].philo_pid, 0, 0);
		i++;
	}
	//printf("clean earl\n"); //del
	err_clean(philos, forks, 0);
}
