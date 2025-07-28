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

int	philo_routine(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		if (!philos[i].dead)
			eating(data, data->philos);
		else
			return (0);
	}
	while (--i > -1)
	{
		if (!philos[i].dead)
			thinking(data, data->philos);
		else
			return (0);
	}
	while (++i < data->num_of_philos)
	{
		if (!philos[i].dead)
			sleeping(data, data->philos);
		else
			return (0);
	}
	philo_routine(data, philos);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac < 5 || ac > 6)
		return (printf("Usage: %s <num_of_philos> <time_to_eat> \
<time_to_sleep> <time_to_die> [num_of_meals]\n", av[0]), 1);
	if (!parse_args(av, data))
		return (printf("Error: Invalid arguments\n"), 1);
	ft_usleep(time);
	if (!philo_routine(data, data->philos))
		return (printf("End routine\n"), 1);
	free(data->philos);
	pthread_mutex_destroy(&data->lock);
	free(data);
	return (0);
}
