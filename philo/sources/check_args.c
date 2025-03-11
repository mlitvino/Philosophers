/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:27:59 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/11 18:40:33 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		error("Error: the invalid argument");
	return (temp);
}

void	check_args(int argc, char *argv[], t_info *info)
{
	int		i;

	i = 1;
	info->stop_flag = 1;
	info->max_philos = convert_arg(argv[i++]);
	info->dth_time = convert_arg(argv[i++]);
	info->eat_time = convert_arg(argv[i++]);
	info->slp_time = convert_arg(argv[i++]);
	if (argc == 6)
		info->meals = convert_arg(argv[i++]);
	else
		info->stop_flag = 0;
}
