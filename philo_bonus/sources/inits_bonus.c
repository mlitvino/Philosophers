/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:01:52 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/13 16:15:53 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*init_philos(t_philo *philos, sem_t *forks, t_info *info)
{
	int	i;

	philos = malloc(sizeof(t_philo) * info->max_philos);
	if (!philos)
	{
		err_clean(philos, forks, 0);
		error("Error: malloc failed in init_philos");
	}
	i = 0;
	while (i < info->max_philos)
	{
		philos[i].philo_i = i + 1;
		philos[i].left = i;
		philos[i].right = (i + 1) % info->max_philos;
		philos[i].philo_pid = -1;
		i++;
	}
	return (philos);
}

int	create_philos(t_philo *philos, t_info *info, sem_t *forks)
{
	int	i;

	i = 0;
	while (i < info->max_philos)
	{
		pid_t pid = fork();
		if (pid == -1)
		{
			err_clean(philos, forks, i);
			error("Error: fork failed child creation");
		}
		else if (pid == 0)
		{
			printf("Philo %d is good\n", i + 1);
			//routine(&philos[i], info, forks);
			exit(0);
		}
		else
			philos[i].philo_pid = pid;
		i++;
	}
	return (0);
}
