/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:21:00 by jpatrici          #+#    #+#             */
/*   Updated: 2025/08/11 20:43:17 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_incs/philo.h"
#include <pthread.h>
#include <unistd.h>

int	monitor_philos(t_data *data, t_philo **philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->lock);
	pthread_mutex_lock(data->death_mutex);
	while (data->stop_routine && i < data->num_of_philos)
	{
		if (philo[++i] && death_check(data, philo[i]))
		{
			data->stop_routine = 0;
			pthread_mutex_unlock(data->death_mutex);
			pthread_mutex_unlock(&data->lock);
			return (0);
		}
	}
	pthread_mutex_unlock(data->death_mutex);
	pthread_mutex_unlock(&data->lock);
	return (1);
}

int	print_death(t_philo *philo)
{
	if (philo->dead == -1)
		return (1);
	if (philo->dead == 1)
		printf("%ld %d has died\n",
			(set_time() - philo->start_time), philo->id);
	return (1);
}

int	death_check(t_data *data, t_philo *philo)
{
	static int	count;

	pthread_mutex_lock(philo->eat_mutex);
	if (data->num_of_meals != -1 && philo->meals_eaten >= data->num_of_meals)
	{
		if (philo->meals_eaten == data->num_of_meals)
			philo->meals_eaten = -1;
		count++;
		if (count == data->num_of_philos)
			return (pthread_mutex_unlock(philo->eat_mutex),
				data->stop_routine = 0, 1);
	}
	if (philo->dead != -1
		&& (set_time() - philo->start_time) - \
philo->last_meal >= data->time_to_die)
		philo->dead = 1;
	pthread_mutex_unlock(philo->eat_mutex);
	if (philo->dead)
	{
		print_death(philo);
		philo->dead = -1;
		return (1);
	}
	return (0);
}
