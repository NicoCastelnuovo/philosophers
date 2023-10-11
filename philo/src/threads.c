/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:54:23 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/11 13:19:39 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_threads(t_monastery *data)
{
	int	i;

	data->time.clock_start = get_abs_time();
	if (!data->time.clock_start)
		return (error(&data->err_code, EGET_TIME, __FILE__, __LINE__));
	if (data->time.eat_limit > 0) // means, if it's 0 there is no limit to it so don't run the th
	{
		if (pthread_create(&data->meal_monitor, NULL, eat_routine, data))
			return (error(&data->err_code, ECREATE_THREAD, __FILE__, __LINE__));
	}
	if (pthread_create(&data->dead_monitor, NULL, death_monitor, data))
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
		else
		i++;
	}
	if (pthread_join(data->dead_monitor, NULL))
		return (error(&data->err_code, ETHJOIN, __FILE__, __LINE__));
	if (data->time.eat_limit > 0)
	{
		if (pthread_join(data->meal_monitor, NULL))
			return (error(&data->err_code, ETHJOIN, __FILE__, __LINE__));
	}
	return (0);
}

int	destroy_mutex(t_monastery *data)
{
	int i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(data->eat_time_locks + i);
		pthread_mutex_destroy(data->meals_locks + i);
		pthread_mutex_destroy(data->forks + i);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->end_lock); // err code for errors !
	// return (error(&data->err_code, EMUTEX_DESTROY, __FILE__, __LINE__));
}
