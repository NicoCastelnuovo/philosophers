/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:40:28 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/12 15:02:35 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*starters(void *arg)
{
	t_philo	*philo;
	long int	curr_time;

	philo = (t_philo *)arg;
	// protection

	// if (philo->personal_turn == 0)
		// start eating
	// else
		// sleep

	// pthread_mutex_lock(philo->mutex);

	// *(philo->r_fork) = 0;
	// curr_time = get_ms() - philo->start;
	// printf("%ld %d has taken a fork.\n", curr_time, philo->id);
	// *(philo->l_fork) = 0;
	// curr_time = get_ms() - philo->start;
	// printf("%ld %d has taken a fork.\n", curr_time, philo->id);
	// curr_time = get_ms() - philo->start;
	// printf("%ld %d is eating.\n", curr_time, philo->id);
	// usleep(philo->eat);
	// *(philo->r_fork) = 1;
	// *(philo->l_fork) = 1;

	// pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

static void	*queued(void *arg)
{
	t_philo		*philo;
	long int	curr_time;

	philo = (t_philo *)arg;
	// curr_time = get_ms() - philo->start;
	// printf("%ld %d is sleeping.\n", curr_time, philo->id);
	// usleep(philo->sleep);
	// pthread_mutex_lock(philo->mutex);

	// pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

int create_threads(t_monastery *data)
{
	int	i;
	int	err_code;

	i = 0;
	err_code = 0;
	while (i < data->n_philo)
	{
		if (data->philo[i]->turn == 0)
		{
			if (pthread_create(data->th + i, NULL, &starters, data->philo[i]))
				return (error(ECREATE_THREAD, __FILE__, __LINE__));
		}
		else if (data->philo[i]->turn == 1)
			if (pthread_create(data->th + i, NULL, &queued, data->philo[i]))
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
