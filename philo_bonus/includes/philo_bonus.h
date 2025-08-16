/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:08:43 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/19 22:55:38 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
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
	sem_t	*globl_dth;
	sem_t	*chk_fork;
}	t_my_sem;

typedef struct s_info
{
	int		max_philos;
	int		dth_time;
	int		eat_time;
	int		slp_time;
	int		meals;
	int		stop_flag;
}	t_info;

typedef struct s_philo
{
	t_my_sem		*forks;
	t_info			*info;

	int				philo_i;
	pthread_t		wait_dth_thrd;
	pthread_t		wait_fork_thrd;
	int				globl_death;
	int				taken_fork;

	long long		dth_date;
	long long		temp_time;
	struct timeval	tv;
}	t_philo;

//check_args.c
long		safe_atoi(const char *str);
long		convert_arg(char *argv);
int			check_args(int argc, char *argv[], t_info *info);

//forks_acts.c
void		*wait_fork_thrd(void *philo_arg);
int			put_forks(t_philo *philo, t_my_sem *forks);
void		create_wait_thread(t_philo *philo, t_my_sem *forks);
void		take_fork(t_philo *philo, t_my_sem *forks);
int			take_forks(t_philo *philo, t_my_sem *forks);

//inits.c
void		delete_old_sem();
void		init_sem(t_my_sem *forks, t_info *info);
int			create_philos(t_philo *philos, t_info *info, t_my_sem *forks);

//main.c
int			main(int argc, char *argv[]);

//routine.c
int			go_sleep(t_philo *philo, t_info *info);
int			go_think(t_philo *philo);
int			is_dead(t_philo *philo, t_my_sem *forks);
int			go_eat(t_philo *philo, t_info *info, t_my_sem *forks);
int			routine(t_philo *philo, t_info *info, t_my_sem *forks, int philo_i);

//utils.c
void		error(char *message);
int			ft_strlen(char *message);
int			ft_isspace(int x);
long long	get_msec(struct timeval *tv);
long long	get_usec(struct timeval *tv);

//wait_clean.c
void		*wait_death(void *new_philo);
void		clean_sem(t_my_sem *forks);
void		wait_clean(t_my_sem *forks);
void		proc_exit_clean(t_my_sem *forks, t_philo *philo);

#endif
