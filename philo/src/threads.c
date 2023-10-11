/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:54:23 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/11 15:05:33 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_odd_th(t_monastery *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (i % 2 != 0)
		{
			if (pthread_create(&(data->philo + i)->th, NULL, philo_routine, (data->philo) + i))
				return (error(&data->err_code, ECREATE_THREAD));
		}
		i++;
	}
	return (0);
}

static int	create_even_th(t_monastery *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (i % 2 == 0)
		{
			if (pthread_create(&(data->philo + i)->th, NULL, philo_routine, (data->philo) + i))
				return (error(&data->err_code, ECREATE_THREAD));
		}
		i++;
	}
	return (0);
}

/*
	First the monitor are created, followed first by the philo whose index
	is odd, and then by the philo whose index is even.
*/
int create_threads(t_monastery *data)
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
	create_odd_th(data);
	create_even_th(data);
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
	// return (error(&data->err_code, EMUTEX_DESTROY));
}
