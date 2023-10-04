/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_monastery.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:46:28 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/04 15:55:49 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_mutex(t_monastery *data)
{
	int	i;

	data->mutex = ft_calloc(data->n_philo, sizeof(pthread_mutex_t));
	if (!data->mutex)
		return (error(EMALLOC, __FILE__, __LINE__));
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(data->mutex + i, NULL) != 0)
			return (error(EMUTEX, __FILE__, __LINE__));
		i++;
	}
	return (0);
}

int	create_monastery(t_monastery *data, char **argv)
{
	int	i;

	// PHILO NUMBER
	data->n_philo = ft_atoi(argv[1]);

	// MUTEXES
	if (create_mutex(data))
		return (1); // substitute (1) with (ECREATE_MUTEX)

	// TIMESTAMP
	data->time = ft_calloc(1, sizeof(t_time));
	if (!data->time)
		return (error(EMALLOC, __FILE__, __LINE__));
	data->time->to_die = ft_atoi(argv[2]); //* 1000;
	data->time->to_eat = ft_atoi(argv[3]); //* 1000;
	data->time->to_sleep = ft_atoi(argv[4]); //* 1000;
	data->time->clock_start = 0;

	// PHILOSOPHERS
	data->philo = create_philo(data);
	if (!data->philo)
		return (error(ECREATE_PHILO, __FILE__, __LINE__));


	// EAT_LIMIT
	/*
		Check if there is a n times each philo has to eat. If yes, data->n_eat_status
		is created to be monitored by the eat_monitor. Each int * points to a philo's
		n_eat.
	*/
	if (argv[5])
		data->time->eat_limit = ft_atoi(argv[5]); // remove and set to (null) ???
	else
		data->time->eat_limit = -1; // remove if not important
	if (data->time->eat_limit > -1)
	{
		data->n_eat_status = ft_calloc(data->n_philo, sizeof(int));
		if (!data->n_eat_status)
			return (error(EMALLOC, __FILE__, __LINE__));
		i = 0;
		while (i < data->n_philo)
		{
			data->n_eat_status[i] = data->philo[i]->n_eat;
			i++;
		}
	}


	// THREADS
	data->th = ft_calloc(data->n_philo + 1, sizeof(pthread_t)); // why + 1 ?????????
	if (!data->th)
		return (error(EMALLOC, __FILE__, __LINE__));


	// END FLAGS
	data->time->someone_is_dead = 0; // shared information
	data->time->everyone_has_eaten = 0; // shared information


	return (0);
}
