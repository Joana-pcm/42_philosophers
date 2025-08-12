/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:00:10 by jpatrici          #+#    #+#             */
/*   Updated: 2025/08/11 20:46:31 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_incs/philo.h"
#include <pthread.h>

int	create_threads(t_data *data, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
		if (pthread_create(&(philos[i]->thread), NULL,
				(void *)philo_routine, philos[i]) != 0)
			return (0);
	i = -1;
	while (++i < data->num_of_philos)
		pthread_join(philos[i]->thread, NULL);
	return (1);
}

void	single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d has picked up a fork\n",
		(set_time() - philo->start_time), philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	ft_usleep(philo->data->time_to_die, philo);
}

int	stop_checker(t_philo *philos)
{
	pthread_mutex_lock(philos->data->death_mutex);
	if (philos->dead == -1 || !philos->data->stop_routine)
		return (0);
	pthread_mutex_unlock(philos->data->death_mutex);
	return (1);
}

void	philo_routine(t_philo *philos)
{
	if (philos->data->num_of_philos == 1)
		return (single_philo(philos));
	while (1)
	{
		if (!stop_checker(philos) || ft_usleep(0, philos)
			|| !stop_checker(philos) || !eating(philos))
			break ;
		if (!stop_checker(philos))
			break ;
		pthread_mutex_lock(philos->print_mutex);
		printf("%ld %d is thinking\n",
			(set_time() - philos->start_time), philos->id);
		pthread_mutex_unlock(philos->print_mutex);
		if (!stop_checker(philos))
			break ;
		pthread_mutex_lock(philos->print_mutex);
		printf("%ld %d is sleeping\n",
			(set_time() - philos->start_time), philos->id);
		pthread_mutex_unlock(philos->print_mutex);
		ft_usleep(philos->data->time_to_sleep, philos);
		if (!stop_checker(philos))
			break ;
	}
	pthread_mutex_unlock(philos->data->death_mutex);
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
	if (parse_args(av, &data))
		create_threads(data, data->philos);
	else
		printf("Error: Invalid arguments\n");
	if (data)
		ft_free_philos(data);
	return (0);
}
