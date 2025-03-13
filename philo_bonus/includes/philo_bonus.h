/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:08:43 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/13 23:45:02 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define _DEFAULT_SOURCE
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define _XOPEN_SOURCE 600
# include <sys/wait.h>

# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

//#define _POSIX_C_SOURCE
#include <signal.h>

typedef struct s_my_sem
{
	sem_t	*forks;
	sem_t	*lock;
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
	struct s_philo	*other;
	pid_t			philo_pid;
	int				philo_i;

	int				left;//del
	int				right;//del

	long long		dth_date;
	long long		eat_date;
	struct timeval	tv;

	long long		temp_time;
}	t_philo;

//check_args.c
long		safe_atoi(const char *str);
long		convert_arg(char *argv);
int			check_args(int argc, char *argv[], t_info *info);

//forks_acts.c
int			put_forks(t_philo *philo, t_my_sem *forks);
int			chck_grap_fork(t_philo *philo, t_my_sem *forks);
int			take_forks(t_philo *philo, t_my_sem *forks, t_info *info);

//inits.c
void		init_sem(t_my_sem *forks, t_info *info);
t_philo		*init_philos(t_philo *philos, t_my_sem *forks, t_info *info);
int			create_philos(t_philo *philos, t_info *info, t_my_sem *forks);

//main.c
int			main(int argc, char *argv[]);

//routine.c
int			is_dead(t_philo *philo);
int			routine(t_philo *philo, t_info *info, t_my_sem *forks);

//utils.c
void		error(char *message);
int			ft_strlen(char *message);
int			ft_isspace(int x);
long long	cur_time(struct timeval	*tv);

//wait_ckean.c
void		err_clean(t_philo *philos, t_my_sem *forks, int max_philos);
void		wait_clean(t_philo *philos, t_my_sem *forks, int max_philos);

//DEL.c
#define Me 4
void		notake_fork(t_philo *philos);
void		see_all(t_philo *philos);
void		*test(void *neew);

#endif
