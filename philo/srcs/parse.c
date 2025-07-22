/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpatrici <jpatrici@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:12:21 by jpatrici          #+#    #+#             */
/*   Updated: 2025/07/11 18:18:25 by jpatrici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_incs/philo.h"

int	parse_args(char **args, t_data *data)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[++i])
		if (!ft_is_num(args[i]))
			return (0);
	data_init(data, args);
	if (data->num_of_philos > 200 || data->num_of_philos < 1)
		return (printf("Invalid number of philosophers\n"), 0);
	return (1);
}
