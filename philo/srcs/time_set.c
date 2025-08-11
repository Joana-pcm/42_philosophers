/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:43:25 by jpatrici          #+#    #+#             */
/*   Updated: 2025/08/11 20:43:26 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_incs/philo.h"

long	set_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(long time, t_philo *philo)
{
	long	start;

	start = set_time();
	if (time == 0 && !monitor_philos(philo->data, philo->data->philos))
		return (1);
	if (time > philo->data->time_to_die)
	{
		ft_usleep(philo->data->time_to_die, philo);
		return (2);
	}
	while (set_time() - start < time)
	{
		usleep(100);
		if (!monitor_philos(philo->data, philo->data->philos))
			return (1);
	}
	return (0);
}
