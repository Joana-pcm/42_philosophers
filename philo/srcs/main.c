/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:00:10 by jpatrici          #+#    #+#             */
/*   Updated: 2025/08/05 18:39:15 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_incs/philo.h"
#include <pthread.h>

int	create_threads(t_data *data, t_philo **philos)
{
	int	i;

	i = -1;
	/*printf("num of philos:\t%ld\n", data->num_of_philos);*/
	while (++i < data->num_of_philos)
	{
		if (pthread_create(&(philos[i]->thread), NULL, (void *)philo_routine, philos[i]) != 0)
			return (0);
	}
	i = -1;
	while (++i < data->num_of_philos)
	{
		pthread_join(philos[i]->thread, NULL);
	}

	return (1);
}

int	philo_routine(t_philo *philos)
{
	while (1)
	{	
		monitor_philos(philos->data, philos->data->philos);
		if (!philos->data->stop_routine)
			break ;
		pthread_mutex_lock(philos->print_mutex);
		eating(philos);
		pthread_mutex_unlock(philos->print_mutex);
		monitor_philos(philos->data, philos->data->philos);
		if (!philos->data->stop_routine)
			break ;
		pthread_mutex_lock(philos->print_mutex);
		thinking(philos);
		pthread_mutex_unlock(philos->print_mutex);
		monitor_philos(philos->data, philos->data->philos);
		if (!philos->data->stop_routine)
			break ;
		pthread_mutex_lock(philos->print_mutex);
		sleeping(philos);
		pthread_mutex_unlock(philos->print_mutex);
		monitor_philos(philos->data, philos->data->philos);
		if (!philos->data->stop_routine)
			break ;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		i;
	t_data	*data;

	data = NULL;
	i = -1;
	if (ac < 5 || ac > 6)
		return (printf("Usage: %s <num_of_philos> <time_to_die> \
<time_to_eat> <time_to_sleep> [num_of_meals]\n", av[0]), 1);
	if (!parse_args(av, &data))
		return (printf("Error: Invalid arguments\n"), 1);
	create_threads(data, data->philos);
	while (++i < data->num_of_philos)
		free(data->philos[i]);
	pthread_mutex_destroy(&(data->lock));
	free(data->philos);
	free(data->fork);
	free(data);
	return (0);
}
