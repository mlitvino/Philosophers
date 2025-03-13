/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:27:59 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/13 12:52:46 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	safe_atoi(const char *str)
{
	long		res;
	int			sign;

	res = 0;
	sign = 1;
	if (str == NULL)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign *= -1;
	if (!(*str >= '0' && *str <= '9'))
		return ((long)INT_MAX + 1);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str++ - '0');
		if (res > INT_MAX || res < INT_MIN)
			return ((long)INT_MAX + 1);
	}
	while (ft_isspace(*str))
		str++;
	if (*str)
		return ((long)INT_MAX + 1);
	return (res * sign);
}

long	convert_arg(char *argv)
{
	long	temp;

	temp = safe_atoi(argv);
	if (temp < 1 || INT_MAX < temp)
		error("Error: invalid argument");
	return (temp);
}

int	check_args(int argc, char *argv[], t_info *info)
{
	info->stop_flag = 1;
	info->meals = 0;
	info->max_philos = convert_arg(argv[1]);
	info->dth_time = convert_arg(argv[2]);
	info->eat_time = convert_arg(argv[3]);
	info->slp_time = convert_arg(argv[4]);
	if (argc == 6)
		info->meals = convert_arg(argv[5]);
	else
		info->stop_flag = 0;
	return (0);
}
