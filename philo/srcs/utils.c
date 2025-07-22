
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

int	ft_is_num(char *num)
{
	int	i;

	i = -1;
	while (num[++i])
		if (num[i] < '0' || num[i] > '9')
			return (0);
	return (1);
}

int data_init(t_data *data, char **args)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->philos = malloc(sizeof(t_philo) * ft_atol(args[1]));
	if (!data->philos)
		return (free(data), 0);
	data->num_of_philos = ft_atol(args[1]);
	data->time_to_eat = ft_atol(args[2]);
	data->time_to_sleep = ft_atol(args[3]);
	data->time_to_die = ft_atol(args[4]);
	if (args[5])
		data->num_of_meals = ft_atol(args[5]);
	else
		data->num_of_meals = -1; 
	return (1);
}
