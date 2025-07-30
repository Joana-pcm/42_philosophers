#include "../t_incs/philo.h"

long	set_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long time)
{
	long	start;

	start = set_time();
	while (set_time() - start < time)
		usleep(100);
}
