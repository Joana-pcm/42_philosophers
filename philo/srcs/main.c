/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:00:10 by jpatrici          #+#    #+#             */
/*   Updated: 2025/07/11 18:10:59 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_incs/philo.h"

int monitor_philos(t_data *data, t_philo **philo)
{
	int	i;
	i = -1;
	while (data->stop_routine)
		if (death_check(data, philo[++i]))
			return (data->stop_routine = 0, 0);
}

int	death_check(t_data *data, t_philo *philo)
{
	static	int	count;
	
	if (data->num_of_meals != -1 && philo->meals_eaten >= data->num_of_meals)
	{
		count++;
		if (count == data->num_of_philos)
			return (data->stop_routine = 0, 1);
	}
	if (set_time() - philo->start_time >= data->time_to_die)	
		philo->dead = 1;
	if (philo->dead)
		return (printf("%ld %d has died\n", (set_time() - philo->start_time), philo->id), 1);
	return (0);
}

int	philo_routine(t_data *data, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		eating(data, data->philos[i]);
		thinking(data, data->philos[i]);
		sleeping(data, data->philos[i]);
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	t_data	*data;

	data = NULL;
	i = -1;
	if (ac < 5 || ac > 6)
		return (printf("Usage: %s <num_of_philos> <time_to_eat> \
<time_to_sleep> <time_to_die> [num_of_meals]\n", av[0]), 1);
	if (!parse_args(av, &data))
		return (printf("Error: Invalid arguments\n"), 1);
	monitor_philos(data, data->philos);
	while (data->stop_routine)
	{
		philo_routine(data, data->philos);
	}
	while (++i < data->num_of_philos)
		free(data->philos[i]);
	pthread_mutex_destroy(&(data->lock));
	free(data->philos);
	free(data->fork);
	free(data);
	return (0);
}
