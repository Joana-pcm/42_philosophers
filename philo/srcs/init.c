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

int	philo_init(t_data **data, t_philo **philo)
{
	int	i;

	i = -1;
	(*data)->philos = malloc(sizeof(t_philo) * (*data)->num_of_philos);
	if (!(*data)->philos)
		return (free(data), 0);
	while (++i < (*data)->num_of_philos)
	{
		philo[i]->id = i;
		
	}
	return (1);
}

int data_init(t_data **data, char **args)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (0);
	(*data)->num_of_philos = ft_atol(args[1]);
	(*data)->time_to_eat = ft_atol(args[2]);
	(*data)->time_to_sleep = ft_atol(args[3]);
	(*data)->time_to_die = ft_atol(args[4]);
	(*data)->philos->dead = 0;
	if (args[5])
		(*data)->num_of_meals = ft_atol(args[5]);
	else
		(*data)->num_of_meals = -1; 
	return (1);
}
