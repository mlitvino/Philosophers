/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_acts_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:18:25 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/17 17:45:23 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	put_forks(t_philo *philo, t_my_sem *forks)
{
	is_dead(philo, 1);
	sem_post(forks->forks);
	sem_post(forks->forks);
	printf("%lld %d put a fork down\n", get_msec(&philo->tv), philo->philo_i);
	printf("%lld %d put a fork down\n", get_msec(&philo->tv), philo->philo_i);
	sem_post(forks->print);
	return (0);
}


/*
	create tread check_global_death

	sem_wait_gl_death
	death = 1
	sem_post_gl_death


	is_dead

		if (death == 1)

*/

/*
	sem_wait_tread
	sem_wait()
	fork = 1;
*/

int	take_forks(t_philo *philo, t_my_sem *forks)
{
	printf("here\n");//DEL
	is_dead(philo, 0);
	sem_post(forks->print);

	sem_wait(forks->lock);

	/*
	create tread sem_wait_tread
	detach_sem_wait
	while(fork != 1)
	{
		usleep(250)
		if (is_dead() == -1)
		{
			sem_post();
			exit(1);
		}
	}
	fork = 0
	*/
	sem_wait(forks->forks);
	sem_wait(forks->print);
	printf("%lld %d has taken a fork\n", get_msec(&philo->tv), philo->philo_i);
	sem_post(forks->print);

	/*
	create sem_wait_tread
	while(fork != 1)
	{
		usleep(250)
		if (is_dead() == -1)
		{
			sem_post();
			exit(1);
		}
	}
	*/
	sem_wait(forks->forks);
	sem_wait(forks->print);
	printf("%lld %d has taken a fork\n", get_msec(&philo->tv), philo->philo_i);
	sem_post(forks->print);

	sem_post(forks->lock);
	return (0);
}
