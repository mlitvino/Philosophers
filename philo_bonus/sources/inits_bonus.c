/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:01:52 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/13 23:47:28 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem(t_my_sem *forks, t_info *info)
{
	forks->forks = sem_open("/forks_sem", O_CREAT | O_EXCL,
		S_IRUSR | S_IWUSR | S_IXUSR, info->max_philos);
	if (forks->forks == SEM_FAILED)
		error("Error: semaphore creation failed");
	forks->lock = sem_open("/lock_sem", O_CREAT | O_EXCL,
		S_IRUSR | S_IWUSR | S_IXUSR, 2);
	if (forks->forks == SEM_FAILED)
	{
		unlink("/forks_sem");
		error("Error: semaphore creation failed");
	}
}

t_philo	*init_philos(t_philo *philos, t_my_sem *forks, t_info *info)
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
		//philos[i].left = i;
		//philos[i].right = (i + 1) % info->max_philos;
		philos[i].philo_pid = -1;
		philos[i].other = philos;
		i++;
	}
	return (philos);
}

int	create_philos(t_philo *philos, t_info *info, t_my_sem *forks)
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
			//printf("Philo %d is good\n", i + 1); //del
			routine(&philos[i], info, forks);
		}
		else
			philos[i].philo_pid = pid;
		i++;
	}
	return (0);
}
