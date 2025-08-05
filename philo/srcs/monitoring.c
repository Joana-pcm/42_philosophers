/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:21:00 by jpatrici          #+#    #+#             */
/*   Updated: 2025/08/04 19:58:28 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_incs/philo.h"

int	death_check(t_philo *philo)
{
	static	int	counter;

	counter = 0;

	if (philo->dead)
		return (printf("%ld %d has died\n", philo->start_time, philo->id), 1);
	return (0);
}
