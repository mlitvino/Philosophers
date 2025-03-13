/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_clean_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:34:11 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/13 15:51:19 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	err_clean(t_philo *philos, sem_t *forks, int max_philos)
{
	int	i;

	i = -1;
	while (++i < max_philos)
		if (philos[i].philo_pid != -1)
			kill(philos[i].philo_pid, SIGTERM);
	sem_close(forks);
	sem_unlink("/forks_sem");
	free(philos);
	philos = NULL;
}

void	wait_clean(t_philo *philos, sem_t *forks, int max_philos)
{
	int	i;

	i = 0;
	while (i < max_philos)
	{
		waitpid(philos[i].philo_pid, 0, 0);
		i++;
	}
	sem_close(forks);
	sem_unlink("/forks_sem");
	free(philos);
	philos = NULL;
}
