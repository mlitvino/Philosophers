/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:52:41 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/11 23:39:40 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(char *message)
{
	write(2, message, ft_strlen(message));
	write(1, "\n", 1);
}

int	ft_strlen(char *message)
{
	int	res;

	res = 0;
	while (message[res])
		res++;
	return (res);
}

int	ft_isspace(int x)
{
	return (x == '\n' || x == '\v' || x == '\t'
		|| x == ' ' || x == '\f' || x == '\r');
}

long long	cur_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
