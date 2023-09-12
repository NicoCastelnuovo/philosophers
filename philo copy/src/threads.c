/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:40:28 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/11 17:46:25 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	pthread_mutex_lock(philo->mutex);
	print_state(philo);
	// if (philo->id == 1)
	// 	printf("This N is (%d)\n", *(philo->n));
	pthread_mutex_unlock(philo->mutex);
}

int create_threads(t_monastery *data)
{
	int	i;
	int	err_code;

	i = 0;
	err_code = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(data->th + i, NULL, &routine, data->philo[i]))
			return (error(ECREATE_THREAD, __FILE__, __LINE__));
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
		if (pthread_join(data->th[i], NULL))
			return (error(ETHJOIN, __FILE__, __LINE__));
		i++;
	}
	return (0);
}
