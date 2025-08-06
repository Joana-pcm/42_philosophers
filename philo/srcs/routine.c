/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:52:01 by jpatrici          #+#    #+#             */
/*   Updated: 2025/08/05 18:28:53 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_incs/philo.h"

int	pickup_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_l);
		/*pthread_mutex_lock(philo->print_mutex);*/
		printf("%ld %d has picked up a fork\n", (set_time() - philo->start_time), philo->id);
		/*pthread_mutex_unlock(philo->print_mutex);*/
		pthread_mutex_lock(philo->fork_r);
		/*pthread_mutex_lock(philo->print_mutex);*/
		printf("%ld %d has picked up a fork\n", (set_time() - philo->start_time), philo->id);
		/*pthread_mutex_unlock(philo->print_mutex);*/
	}
	else
	{
		pthread_mutex_lock(philo->fork_r);
		/*pthread_mutex_lock(philo->print_mutex);*/
		printf("%ld %d has picked up a fork\n", (set_time() - philo->start_time), philo->id);
		/*pthread_mutex_unlock(philo->print_mutex);*/
		pthread_mutex_lock(philo->fork_l);
		/*pthread_mutex_lock(philo->print_mutex);*/
		printf("%ld %d has picked up a fork\n", (set_time() - philo->start_time), philo->id);
		/*pthread_mutex_unlock(philo->print_mutex);*/
	}
	return (1);
}

int	thinking(t_philo *philo)
{
	/*pthread_mutex_lock(philo->print_mutex);*/
	printf("%ld %d is thinking\n", (set_time() - philo->start_time), philo->id);
	/*pthread_mutex_unlock(philo->print_mutex);*/
	return (1);
}

int	eating(t_philo *philo)
{
	pickup_fork(philo);
	philo->last_meal = set_time() - philo->start_time;
	if (philo->data->num_of_meals > -1)
		philo->meals_eaten++;
	/*pthread_mutex_lock(philo->print_mutex);*/
	printf("%ld %d is eating\n", philo->last_meal, philo->id);
	/*pthread_mutex_unlock(philo->print_mutex);*/
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	ft_usleep(philo->data->time_to_eat);
	return (1);
}

int	sleeping(t_philo *philo)
{
	/*pthread_mutex_lock(philo->print_mutex);*/
	printf("%ld %d is sleeping\n", (set_time() - philo->start_time), philo->id);
	/*pthread_mutex_unlock(philo->print_mutex);*/
	ft_usleep(philo->data->time_to_sleep);
	return (1);
}
