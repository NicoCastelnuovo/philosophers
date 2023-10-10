/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:54:23 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/10 15:42:33 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	share_clock_start(t_monastery *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->n_philo)
// 	{
// 		(data->philo + i)->time.clock_start = data->time.clock_start;
// 		i++;
// 	}
// }

int create_threads(t_monastery *data)
{
	int	i;

	data->time.clock_start = get_abs_time(); // move it right-before the starting threads ???
	// share_clock_start(data);
	if (!data->time.clock_start)
		return (error(&data->err_code, EGET_TIME, __FILE__, __LINE__));
	// if (data->time.eat_limit >= 0) // right??? -- what happens in case of -1 input??
	// {
	// 	if (pthread_create(&data->th_eat_monitor, NULL, eat_routine, data))
	// 		return (error(&data->err_code, ECREATE_THREAD, __FILE__, __LINE__));
	// }
	if (pthread_create(&data->th_dead_monitor, NULL, monitor_routine, data))
		return (error(&data->err_code, ECREATE_THREAD, __FILE__, __LINE__));
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&(data->philo + i)->th, NULL, philo_routine, (data->philo) + i))
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
		if (pthread_join((data->philo + i)->th, NULL))
			return (error(&data->err_code, ETHJOIN, __FILE__, __LINE__));
		i++;
	}
	if (pthread_join(data->th_dead_monitor, NULL))
		return (error(&data->err_code, ETHJOIN, __FILE__, __LINE__));
	if (data->time.eat_limit > -1)
	{
		if (pthread_join(data->th_eat_monitor, NULL)) // only if present
			return (error(&data->err_code, ETHJOIN, __FILE__, __LINE__));
	}
	return (0);
}
