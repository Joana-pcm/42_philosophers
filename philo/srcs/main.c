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

int	death_check(t_philo *philo)
{
	/*int	i;*/
	/**/
	/*i = -1;*/
	/*while (++i < data->num_of_philos)*/
	/*{*/
		if (philo->dead)
			return (printf("%ld %d has died\n", philo->start_time, philo->id), 1);
		/*if (data->num_of_meals)*/
	/*}*/
	return (0);
}

int	philo_routine(t_data *data, t_philo **philos)
{
	int	i;

	i = -1;
	/*pickup_fork(data, philos);*/
	while (++i < data->num_of_philos)
	{
		eating(data, data->philos[i]);
		thinking(data, data->philos[i]);
		sleeping(data, data->philos[i]);
		if (death_check(philos[i]))
			return (data->stop_routine = 0, 0);
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
