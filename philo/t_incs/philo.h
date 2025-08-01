#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				id;
	int				dead;
	int				meals_eaten;
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
	int				stop_routine;
	pthread_mutex_t	lock;
	pthread_mutex_t *fork;
	t_philo			**philos;
}	t_data;

long			ft_atol(const char *nptr);
int				ft_is_num(char *num);
int				parse_args(char **args, t_data **data);
int				data_init(t_data **data, char **args);
int				ft_usleep(long time);
long			set_time(void);
int				eating(t_data *data, t_philo *philo);
int				thinking(t_data *data, t_philo *philo);
int				sleeping(t_data *data, t_philo *philo);
t_philo			**philo_init(t_data **data, pthread_mutex_t *fork);
pthread_mutex_t	*fork_init(t_data *data);
int				set_philos_times(t_data *data);

#endif
