/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:50:06 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/11 15:51:38 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_forks(t_monastery *data)
{
	int	i;

	data->forks = ft_calloc(data->n_philo, sizeof(pthread_mutex_t));
	if (!data->forks)
		return (error(&data->err_code, EMALLOC));
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(data->forks + i, NULL))
			return (error(&data->err_code, EMUTEX_INIT));
		i++;
	}
	return (0);
}

int	create_locks(t_monastery *data)
{
	int		i;

	if (create_forks(data))
		return (error(&data->err_code, EMUTEX_INIT));
	if (pthread_mutex_init(&data->end_lock, NULL))
		return (error(&data->err_code, EMUTEX_INIT));
	i = 0;
	data->eat_time_locks = ft_calloc(data->n_philo, sizeof(pthread_mutex_t));
	if (!data->eat_time_locks)
		return (error(&data->err_code, EMALLOC));
	data->meals_locks = ft_calloc(data->n_philo, sizeof(pthread_mutex_t));
	if (!data->meals_locks)
		return (error(&data->err_code, EMALLOC));
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(data->eat_time_locks + i, NULL))
			return (error(&data->err_code, EMUTEX_INIT));
		if (pthread_mutex_init(data->meals_locks + i, NULL))
			return (error(&data->err_code, EMUTEX_INIT));
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (error(&data->err_code, EMUTEX_INIT));
	return (0);
}

int	destroy_mutex(t_monastery *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_destroy(data->eat_time_locks + i))
			return (error(&data->err_code, EMUTEX_DESTROY));
		if (pthread_mutex_destroy(data->meals_locks + i))
			return (error(&data->err_code, EMUTEX_DESTROY));
		if (pthread_mutex_destroy(data->forks + i))
			return (error(&data->err_code, EMUTEX_DESTROY));
		i++;
	}
	if (pthread_mutex_destroy(&data->print_lock))
		return (error(&data->err_code, EMUTEX_DESTROY));
	if (pthread_mutex_destroy(&data->end_lock))
		return (error(&data->err_code, EMUTEX_DESTROY));
	return (0);
}
