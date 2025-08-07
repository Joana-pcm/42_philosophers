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
	while (++i < (*data)->num_of_philos)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->id = i + 1;
		philo[i]->start_time = set_time();
		philo[i]->meals_eaten = 0;
		philo[i]->last_meal = 0;
		philo[i]->dead = 0;
		philo[i]->fork_l = &fork[i];
		philo[i]->fork_r = &fork[(i + 1) % (*data)->num_of_philos];
		philo[i]->eat_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i]->eat_mutex, NULL);
		philo[i]->print_mutex = &(*data)->lock;
		philo[i]->data = *data;
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
	(*data)->time_to_die = ft_atol(args[2]);
	(*data)->time_to_eat = ft_atol(args[3]);
	(*data)->time_to_sleep = ft_atol(args[4]);
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

int	parse_args(char **args, t_data **data)
{
	int	i;

	i = 0;
	if (!args || !args[i + 1])
		return (0);
	while (args[++i])
		if (!ft_is_num(args[i]))
			return (0);
	data_init(data, args);
	if ((*data)->time_to_die < 1
	|| (*data)->time_to_eat < 1
	|| (*data)->time_to_sleep < 1)
		return (0);
	if ((*data)->num_of_philos > 200 || (*data)->num_of_philos < 1)
		return (printf("Invalid number of philosophers\n"), 0);
	return (1);
}
