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

int	philo_routine(t_data *data, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		eating(data, philos[i]);
		thinking(data, philos[i]);
		sleeping(data, philos[i]);
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
		return (printf("Usage: %s <num_of_philos> <time_to_die> \
<time_to_eat> <time_to_sleep> [num_of_meals]\n", av[0]), 1);
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
