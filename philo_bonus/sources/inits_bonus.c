/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:01:52 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/17 00:15:05 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem(t_philo *philos, t_my_sem *forks, t_info *info)
{
	forks->forks = sem_open("/forks_sem", O_CREAT | O_EXCL,
		S_IRUSR | S_IWUSR | S_IXUSR, info->max_philos + 1);
	forks->lock = sem_open("/lock_sem", O_CREAT | O_EXCL,
		S_IRUSR | S_IWUSR | S_IXUSR, 2);
	forks->print = sem_open("/print_sem", O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR | S_IXUSR, 2);
	if (forks->forks == SEM_FAILED || forks->lock == SEM_FAILED
	|| forks->print == SEM_FAILED)
	{
		err_clean(philos, forks, 1);
		error("Error: semaphore creation failed");
	}
}

// pid_t	*create_list(t_info *info, pid_t new_chld, t_my_sem *forks)
// {
// 	pid_t	*child_list;

// 	child_list = malloc(sizeof(pid_t) * info->max_philos);
// 	if (!child_list)
// 	{
// 		kill(new_chld, SIGTERM);
// 		err_clean(NULL, forks, 0);
// 		error("Error: malloc failed in create_list");
// 	}
// 	return (child_list);
// }

int	create_philos(t_philo *philos, t_info *info, t_my_sem *forks)
{
	int		i;
	//pid_t	*child_list;

	i = 0;
	//child_list = NULL;
	while (i < info->max_philos)
	{
		pid_t pid = fork();
		if (pid == -1)
		{
			err_clean(philos, forks, 0);
			error("Error: fork failed child creation");
		}
		else if (pid == 0)
			routine(philos, info, forks, i + 1);
		// else
		// {
		// 	if (!child_list)
		// 		child_list = create_list(info, pid, forks);
		// 	child_list[i] = pid;
		// }
		i++;
	}
	return (0);
}
