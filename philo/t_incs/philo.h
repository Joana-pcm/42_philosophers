#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	struct timeval	start_time;
}	t_philo;

typedef struct s_data
{
	long			num_of_philos;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	long			num_of_meals;
	pthread_mutex_t	lock;
	t_philo			*philos;
}	t_data;

int		ft_atol(const char *nptr);
int		ft_is_num(char *num);
int		parse_args(char **args, t_data *data);
int		data_init(t_data *data, char **args);

#endif