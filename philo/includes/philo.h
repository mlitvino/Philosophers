/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:08:43 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/12 16:22:25 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define _DEFAULT_SOURCE
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_forks
{
	bool			fork;
	pthread_mutex_t	lock;
}	t_forks;

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
	t_info			*info;
	t_forks			*forks;

	pthread_t		philo_th;
	int				philo_id;

	int				left;
	bool			flg_left;
	int				right;
	bool			flg_rigt;

	long long		dth_date;
	long long		eat_date;
	struct timeval	time;

	long long		temp_time;

	struct timeval	str_time;
	long long		cur_time;
}	t_philo;

//check_args.c
long	safe_atoi(const char *str);
long	convert_arg(char *argv);
int		check_args(int argc, char *argv[], t_info *info);

//forks_acts.c
int		put_forks(t_philo *philo);
int		take_fork(t_forks *forks, int fork_i, t_philo *philo);
int		take_forks(t_philo *philo);

//inits.c
t_forks	*init_forks(t_forks *forks, int max_philos);
t_philo	*init_philos(t_philo *philos, t_forks *forks, t_info *info);
int		create_philos(t_philo *philos, t_info *info);

//join_ckean.c
void	destroy_mutex(t_forks *forks, int max_i);
void	join_clean(t_philo *philos, t_info *info);

//main.c
int		main(int argc, char *argv[]);

//routine.c
int		is_died(t_philo *philo);
void	*routine(void *philo);

//utils.c
void	error(char *message);
int		ft_strlen(char *message);
int		ft_isspace(int x);
long long	cur_time(void);

//DEL.c
#define Me 4
void	notake_fork(t_philo *philos);
void	see_all(t_philo *philos);
void	*test(void *new);

#endif
