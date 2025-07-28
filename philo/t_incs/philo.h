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
	int				dead;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*print_mutex;
	suseconds_t		start_time;
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

int				ft_atol(const char *nptr);
int				ft_is_num(char *num);
int				parse_args(char **args, t_data *data);
int				data_init(t_data **data, char **args);
int				eating(t_data *data, t_philo *philo);
int				thinking(t_data *data, t_philo *philo);
int				sleeping(t_data *data, t_philo *philo);
int				philo_init(t_data **data, t_philo **philo, pthread_mutex_t *fork);
pthread_mutex_t	*fork_init(t_data *data);

#endif
