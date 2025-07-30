/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:52:01 by jpatrici          #+#    #+#             */
/*   Updated: 2025/07/29 19:20:14 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_incs/philo.h"

/*int	pickup_fork(t_data *data, t_philo *philo)*/
/*{*/
/**/
/*	return (1);*/
/*}*/

int	thinking(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d is thinking\n", philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	(void)data; // To avoid unused parameter warning
	return (1);
}

int	eating(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	printf("%ld %d has picked up a fork\n", philo->start_time, philo->id);
	pthread_mutex_lock(philo->fork_r);
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d is eating\n", philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	return (1);
}

int	sleeping(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d is sleeping\n", philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	ft_usleep(data->time_to_sleep);
	return (1);
}
