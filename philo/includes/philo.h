/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:08:43 by mlitvino          #+#    #+#             */
/*   Updated: 2025/03/05 16:14:10 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_
# include "libft.h"

typedef struct s_philo
{
	int		i;
	char	*name;
	int		eat_time;
	int		slp_time;
	int		thnk_time;
}	t_philo;


#endif
