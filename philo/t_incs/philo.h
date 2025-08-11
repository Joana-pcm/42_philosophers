/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:34:48 by jpatrici          #+#    #+#             */
/*   Updated: 2025/08/11 20:45:19 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				meals_eaten;
	long			last_meal;
	int				test;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*eat_mutex;
	pthread_t		thread;
	pthread_mutex_t	*print_mutex;
	suseconds_t		start_time;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	long			num_of_philos;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			num_of_meals;
	int				stop_routine;
	pthread_mutex_t	lock;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*death_mutex;
	t_philo			**philos;
}	t_data;

long			ft_atol(const char *nptr);
int				ft_is_num(char *num);
int				stop_checker(t_philo *philos);
int				parse_args(char **args, t_data **data);
int				data_init(t_data **data, char **args);
int				death_check(t_data *data, t_philo *philo);
int				monitor_philos(t_data *data, t_philo **philo);
int				ft_usleep(long time, t_philo *philo);
long			set_time(void);
void			philo_routine(t_philo *philos);
int				eating(t_philo *philo);
t_philo			**philo_init(t_data **data, pthread_mutex_t *fork);
pthread_mutex_t	*fork_init(t_data *data);

#endif
