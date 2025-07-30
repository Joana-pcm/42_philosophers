/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:07:11 by jpatrici          #+#    #+#             */
/*   Updated: 2025/07/23 16:26:39 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_incs/philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

pthread_mutex_t	*fork_init(t_data *data)
{
	pthread_mutex_t	*fork;
	int				i;

	i = -1;
	fork = NULL;
	fork = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	while (++i < data->num_of_philos)
	{
		if(pthread_mutex_init(&fork[i], NULL))
			return (free(data), NULL);
	}
	return (fork);
}

t_philo	**philo_init(t_data **data, pthread_mutex_t *fork)
{
	int		i;
	t_philo	**philo;

	i = -1;
	philo = malloc(sizeof(t_philo *) * ((*data)->num_of_philos + 1));
	if (!philo)
		return (free(data), NULL);
	philo[(*data)->num_of_philos] = NULL;
	/*printf("%ld\n", (*data)->num_of_philos);*/
	while (++i < (*data)->num_of_philos)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->id = i + 1;
		philo[i]->start_time = 0;
		philo[i]->dead = 0;
		philo[i]->fork_l = &fork[i];
		philo[i]->fork_r = &fork[(i + 1) % (*data)->num_of_philos];
		philo[i]->print_mutex = &(*data)->lock;
	}
	return (philo);
}

int data_init(t_data **data, char **args)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (0);
	(*data)->fork = NULL;
	(*data)->num_of_philos = ft_atol(args[1]);
	(*data)->time_to_eat = ft_atol(args[2]);
	(*data)->time_to_sleep = ft_atol(args[3]);
	(*data)->time_to_die = ft_atol(args[4]);
	(*data)->stop_routine = 1;
	pthread_mutex_init(&(*data)->lock, NULL);
	if (args[5])
		(*data)->num_of_meals = ft_atol(args[5]);
	else
		(*data)->num_of_meals = -1;
	(*data)->fork = fork_init(*data);
	if ((*data)->fork)
		(*data)->philos = philo_init(data, (*data)->fork);
	return (1);
}
