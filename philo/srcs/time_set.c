#include "../t_incs/philo.h"

int set_philo_start_time(t_philo *philo)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	philo->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (1);
}
int set_philos_start_time(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (!set_philo_start_time(&data->philos[i]))
			return (0);
		i++;
	}
	return (1);
}
int ft_usleep(long time)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed;

	if (gettimeofday(&start, NULL) != 0)
		return (0);
	while (1)
	{
		if (gettimeofday(&current, NULL) != 0)
			return (0);
		elapsed = (current.tv_sec - start.tv_sec) * 1000 + 
				  (current.tv_usec - start.tv_usec) / 1000;
		if (elapsed >= time)
			break ;
		usleep(100); // Sleep for a short duration to avoid busy waiting
	}
	return (1);
}
int set_philos_times(t_data *data)
{
	if (!set_philos_start_time(data))
		return (0);
	if (!ft_usleep(data->time_to_eat + data->time_to_sleep))
		return (0);
	return (1);
}