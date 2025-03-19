/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:08:43 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/19 19:21:56 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_forks
{
	bool			fork;
	pthread_mutex_t	fork_lock;
	int				queue;
}	t_forks;

typedef struct s_info
{
	int				max_philos;
	long long		dth_time;
	long long		eat_time;
	long long		slp_time;
	int				meals;
	bool			stop_flag;

	pthread_mutex_t	print_lock;
	bool			death;
}	t_info;

typedef struct s_philo
{
	t_info			*info;
	t_forks			*forks;

	pthread_t		philo_th;
	int				philo_id;

	int				left;
	int				right;

	long long		dth_date;
	long long		temp_time;
	struct timeval	tv;
}	t_philo;

//check_args.c
long		safe_atoi(const char *str);
long		convert_arg(char *argv);
int			check_args(int argc, char *argv[], t_info *info);

//forks_acts.c
int			put_forks(t_philo *philo, t_forks *forks, t_info *info);
int			take_both(t_philo *philo, t_forks *forks);
int			check_fork(t_philo *philo, t_forks *forks, int fork_i, int res);
//int			chck_wait_fork(t_philo *philo, t_forks *forks, int first, int second);
int			chck_wait_fork(t_philo *philo, t_forks *forks, int first);
int			take_forks(t_philo *philo, t_forks *forks);

//inits.c
t_forks		*init_forks(t_philo *philos, t_forks *forks, t_info *info);
t_philo		*init_philos(t_philo *philos, t_forks *forks, t_info *info);
int			create_philos(t_philo *philos, t_info *info);

//join_ckean.c
void		destroy_mutex(t_philo *philos, t_forks *forks, int max_i);
void		join_clean(t_philo *philos, t_info *info);

//main.c
int			main(int argc, char *argv[]);

//routine.c
int			go_sleep(t_philo *philo, t_info *info);
int			go_think(t_philo *philo, t_info *info);
int			is_dead(t_philo *philo, t_info *info);
int			go_eat(t_philo *philo, t_info *info);
void		*routine(void *philo);

//utils.c
void		error(char *message);
int			ft_strlen(char *message);
int			ft_isspace(int x);
long long	get_msec(struct timeval *tv);
long long	get_usec(struct timeval *tv);

#endif
