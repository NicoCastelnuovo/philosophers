/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_monastery.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:46:28 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/14 13:32:59 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_monastery(t_monastery *data, char **argv)
{
	int	i;

	// PHILO NUMBER
	data->n_philo = ft_atoi(argv[1]);

	// MUTEXES
	data->mutex = ft_calloc(data->n_philo, sizeof(pthread_mutex_t));
	if (!data->mutex)
		return (error(EMALLOC, __FILE__, __LINE__));
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(data->mutex + i, NULL))
			return (error(EMUTEX, __FILE__, __LINE__));
		i++;
	}

	// TIMESTAMP
	data->time = ft_calloc(1, sizeof(t_time));
	if (!data->time)
		return (error(EMALLOC, __FILE__, __LINE__));
	data->time->to_die = ft_atoi(argv[2]); //* 1000;
	data->time->to_eat = ft_atoi(argv[3]); //* 1000;
	data->time->to_sleep = ft_atoi(argv[4]); //* 1000;
	if (argv[5])
		data->time->limit = ft_atoi(argv[5]);
	else
		data->time->limit = 0; // remove if not important
	data->time->clock_start = 0;
	data->time->is_end = 0;


	// FORKS
	data->forks = ft_calloc(data->n_philo, sizeof(int));
	if (!data->forks)
		return (error(EMALLOC, __FILE__, __LINE__));
	i = 0;
	while (i < data->n_philo)
	{
		data->forks[i] = 0; // ------------- giving an id to the forks just to recognize!
		i++;
	}

	// PHILOSOPHERS
	data->philo = create_philo(data);
	if (!data->philo)
		return (error(ECREATE_PHILO, __FILE__, __LINE__));

	// THREADS
	data->th = ft_calloc(data->n_philo + 1, sizeof(pthread_t));
	if (!data->th)
		return (error(EMALLOC, __FILE__, __LINE__));

	return (0);
}
