/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:08:43 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/17 00:40:14 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# include <sys/wait.h>

# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_my_sem
{
	sem_t	*forks;
	sem_t	*lock;
	sem_t	*print;
}	t_my_sem;

typedef struct s_info
{
	int		max_philos;
	int		dth_time;
	int		eat_time;
	int		slp_time;
	int		meals;
	bool	stop_flag;
}	t_info;

typedef struct s_philo
{
	t_my_sem		*forks;
	t_info			*info;
	int				philo_i;

	long long		dth_date;
	long long		temp_time;
	long long		check_time;
	struct timeval	tv;

}	t_philo;

//check_args.c
long		safe_atoi(const char *str);
long		convert_arg(char *argv);
int			check_args(int argc, char *argv[], t_info *info);

//forks_acts.c
int			put_forks(t_philo *philo, t_my_sem *forks);
int			take_forks(t_philo *philo, t_my_sem *forks);

//inits.c
void		init_sem(t_philo *philos, t_my_sem *forks, t_info *info);
t_philo		*init_philos(t_philo *philos, t_my_sem *forks, t_info *info);
int			create_philos(t_philo *philos, t_info *info, t_my_sem *forks);

//main.c
int			main(int argc, char *argv[]);

//routine.c
int			is_dead(t_philo *philo, int mod);
int			routine(t_philo *philo, t_info *info, t_my_sem *forks, int philo_i);

//utils.c
void		error(char *message);
int			ft_strlen(char *message);
int			ft_isspace(int x);
long long	get_msec(struct timeval *tv);
long long	get_usec(struct timeval *tv);

//wait_ckean.c
void		err_clean(t_philo *philos, t_my_sem *forks, int mod);
void		wait_clean(t_philo *philos, t_my_sem *forks, int max_philos);

#endif
