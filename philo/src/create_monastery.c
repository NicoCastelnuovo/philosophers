/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_monastery.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:46:28 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/17 08:31:20 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	if no eat_limit is set, is just put as -1. if the n_philos is odd, they
	will think for a while after sleeping, otherwise not.
*/
static void	set_ttable(t_monastery *data, char **argv)
{
	data->time.to_die = ft_atol(argv[2]);
	data->time.to_eat = ft_atol(argv[3]);
	data->time.to_sleep = ft_atol(argv[4]);
	data->time.eat_limit = -1;
	if (argv[5])
		data->time.eat_limit = ft_atol(argv[5]);
	data->time.clock_start = 0;
}

int	create_monastery(t_monastery *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error(&data->err_code, EARG));
	if (!is_valid_input(argv))
		return (error(&data->err_code, EARG));
	data->n_philo = ft_atol(argv[1]);
	set_ttable(data, argv);
	if (create_locks(data))
		return (data->err_code);
	data->philo = create_philo(data);
	if (!data->philo)
		return (error(&data->err_code, ECREATE_PHILO));
	data->end_flag = 0;
	return (0);
}
