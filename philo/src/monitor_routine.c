/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:27:25 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/10 17:02:31 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	dead_monitor check if the philo is dead. It compares the time_to_die with
	the moment in which the philo went to sleep or began to eat. If those
	interval are equal to time_to_die, means that philo died.
*/
static int	is_philo_dead(t_monastery *data, int i)
{
	t_philo *philo;

	pthread_mutex_lock(&data->end_lock);
	if (data->end_flag)
	{
		pthread_mutex_unlock(&data->end_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->end_lock);
	philo = data->philo + i;
	pthread_mutex_lock(philo->eat_time_lock);
	if (get_rel_time(data->time.clock_start) - philo->last_eat_time > data->time.to_die) // >= OR >????
	{
		pthread_mutex_unlock(philo->eat_time_lock);
		pthread_mutex_lock(&data->end_lock);
		if (!data->end_flag)
			data->end_flag = 1;
		// else
		// {
		// 	pthread_mutex_unlock(&data->end_lock);
		// 	return (1);
		// }
		pthread_mutex_unlock(&data->end_lock);

		pthread_mutex_lock(&data->print_lock);
		printf("%llu %d died\n", get_rel_time(data->time.clock_start), i + 1);
		pthread_mutex_unlock(&data->print_lock);

		return (1);
	}
	pthread_mutex_unlock(philo->eat_time_lock);
	return (0);
}


void	*death_monitor(void *arg)
{
	t_monastery	*data;
	int64_t		clock_start;
	int			i;

	data = (t_monastery *)arg;
	clock_start = data->time.clock_start;
	i = 0;
	while (1)
	{
		if (is_philo_dead(data, i))
			break ;
		i++;
		if (i == data->n_philo)
		{
			i = 0;
			// usleep(500);
		}
	}
	return (NULL);
}

void	*eat_routine(void *arg)
{
	t_monastery	*data;
	int			i;
	int			n_done;

	data = (t_monastery *) arg;
	i = 0;
	n_done = 0;
	while (1)
	{
		pthread_mutex_lock(&data->end_lock);
		if (data->end_flag)
		{
			pthread_mutex_unlock(&data->end_lock);
			break ;
		}
		pthread_mutex_unlock(&data->end_lock);
		pthread_mutex_lock(data->meals_locks + i);
		if ((data->philo + i)->n_meals >= data->time.eat_limit)
			n_done++;
		pthread_mutex_unlock(data->meals_locks + i);
		i++;
		if (i == data->n_philo)
		{
			if (n_done == data->n_philo)
			{
				pthread_mutex_lock(&data->end_lock);
				if (!data->end_flag)
					data->end_flag = 1;
				pthread_mutex_unlock(&data->end_lock);
				break ;
			}
			n_done = 0;
			i = 0;
			// usleep(500);
		}
	}
	return (NULL);
}
