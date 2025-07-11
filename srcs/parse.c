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

int	ft_is_num(char *num)
{
	int	i;

	i = -1;
	while (num[++i])
		if (num[i] < '0' || num[i] > '9')
			return (0);
	return (1);
}

int	parse_args(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if (!ft_is_num(args[i]))
			return (0);
	}
}
