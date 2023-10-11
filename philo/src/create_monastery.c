/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_monastery.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:46:28 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/11 16:58:33 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_input(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (i < 5)
		{
			if (ft_atol(argv[i]) <= 0)
				return (0);
		}
		else
		{
			if (ft_atol(argv[i]) < 0)
				return (0);
		}
		i++;
	}
	return (1);
}

static void	set_ttable(t_monastery *data, char **argv)
{
	data->time.to_die = ft_atol(argv[2]);
	data->time.to_eat = ft_atol(argv[3]);
	data->time.to_sleep = ft_atol(argv[4]);
	data->time.eat_limit = 0;
	if (argv[5])
		data->time.eat_limit = ft_atol(argv[5]);
	data->time.to_think = 0;
	if (data->n_philo % 2)
		data->time.to_think = 1;
	data->time.clock_start = 0;
}

int	create_monastery(t_monastery *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error(&data->err_code, EARG));
	data->n_philo = ft_atol(argv[1]);
	if (!is_valid_input(argv))
		return (error(&data->err_code, EARG));
	set_ttable(data, argv);
	if (create_locks(data))
		return (data->err_code);
	data->philo = create_philo(data);
	if (!data->philo)
		return (error(&data->err_code, ECREATE_PHILO));
	data->end_flag = 0;
	return (0);
}
