
#include "../t_incs/philo.h"

int	ft_atol(const char *nptr)
{
	long	res;
	int		i;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	if (*nptr == '\010')
		return (0);
	while ((nptr[i] >= '\b' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9') && nptr[i] != '\0')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	res *= sign;
	return (res);
}
int	thinking(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d is thinking\n", philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	(void)data; // To avoid unused parameter warning
	return (1);
}
int	eating(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	pthread_mutex_lock(philo->fork_r);
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d is eating\n", philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	return (1);
}
int	sleeping(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d is sleeping\n", philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	usleep(data->time_to_sleep * 1000);
	return (1);
}

int	ft_is_num(char *num)
{
	int	i;

	i = -1;
	while (num[++i])
		if (num[i] < '0' || num[i] > '9')
			return (0);
	return (1);
}
