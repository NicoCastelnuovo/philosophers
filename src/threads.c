/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:54:23 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/12 14:35:07 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_philo_threads(t_monastery *data, int is_odd_turn)
{
	int			i;
	pthread_t	*th;

	i = 0;
	while (i < data->n_philo)
	{
		th = &(data->philo + i)->th;
		if (is_odd_turn && i % 2 != 0)
		{
			if (pthread_create(th, NULL, philo_routine, (data->philo) + i))
				return (1);
		}
		else if (!is_odd_turn && i % 2 == 0)
		{
			if (pthread_create(th, NULL, philo_routine, (data->philo) + i))
				return (1);
		}
		i++;
	}
	return (0);
}

/*
	First the monitor are created, followed first by the philo whose index
	is odd, and then by the philo whose index is even.
*/
int	create_threads(t_monastery *data)
{
	data->time.clock_start = get_abs_time();
	if (!data->time.clock_start)
		return (error(&data->err_code, EGET_TIME));
	if (data->time.eat_limit > 0)
	{
		if (pthread_create(&data->meal_monitor, NULL, eat_routine, data))
			return (error(&data->err_code, ECREATE_THREAD));
	}
	if (pthread_create(&data->dead_monitor, NULL, death_monitor, data))
		return (error(&data->err_code, ECREATE_THREAD));
	if (create_philo_threads(data, 1))
		return (error(&data->err_code, ECREATE_THREAD));
	if (create_philo_threads(data, 0))
		return (error(&data->err_code, ECREATE_THREAD));
	return (0);
}

int	join_threads(t_monastery *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join((data->philo + i)->th, NULL))
			return (error(&data->err_code, ETHJOIN));
		i++;
	}
	if (pthread_join(data->dead_monitor, NULL))
		return (error(&data->err_code, ETHJOIN));
	if (data->time.eat_limit > 0)
	{
		if (pthread_join(data->meal_monitor, NULL))
			return (error(&data->err_code, ETHJOIN));
	}
	return (0);
}
