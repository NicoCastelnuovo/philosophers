/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:40:28 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/06 10:39:50 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_threads(t_monastery *data)
{
	int	i;

	i = 0;
	data->time->clock_start = get_time_us(); // move it right-before the starting threads ???
	if (!data->time->clock_start)
		return (error(&data->err_code, EGET_TIME, __FILE__, __LINE__));
	if (data->time->eat_limit >= 0) // right??? -- what happens in case of -1 input??
	{
		if (pthread_create(&data->th_eat_monitor, NULL, eat_routine, data))
			return (error(&data->err_code, ECREATE_THREAD, __FILE__, __LINE__));
	}
	if (pthread_create(&data->th_dead_monitor, NULL, monitor_routine, data))
		return (error(&data->err_code, ECREATE_THREAD, __FILE__, __LINE__));
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philo[i]->th, NULL, philo_routine, data->philo[i]))
			return (error(&data->err_code, ECREATE_THREAD, __FILE__, __LINE__));
		i++;
	}
	return (0);
}

int	join_threads(t_monastery *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_join(data->philo[i]->th, NULL))
			return (error(&data->err_code, ETHJOIN, __FILE__, __LINE__));
		i++;
	}
	if (pthread_join(data->th_dead_monitor, NULL))
		return (error(&data->err_code, ETHJOIN, __FILE__, __LINE__));
	if (data->time->eat_limit > -1)
	{
		if (pthread_join(data->th_eat_monitor, NULL)) // only if present
			return (error(&data->err_code, ETHJOIN, __FILE__, __LINE__));
	}
	return (0);
}
