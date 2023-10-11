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

static int	sad_end(t_monastery *data)
{
	pthread_mutex_lock(&data->end_lock); // change the stuff passed inside here and the other functions!
	if (!data->end_flag)
		data->end_flag = 1;
	else
	{
		pthread_mutex_unlock(&data->end_lock);
		return (0);
	}
	pthread_mutex_unlock(&data->end_lock);
	return (1);
}

static int	happy_end(t_monastery *data)
{
	pthread_mutex_lock(&data->end_lock);
	if (!data->end_flag)
		data->end_flag = 1;
	pthread_mutex_unlock(&data->end_lock);
}

static int	is_end_flag_set(t_monastery *data)
{
	pthread_mutex_lock(&data->end_lock);
	if (data->end_flag)
	{
		pthread_mutex_unlock(&data->end_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->end_lock);
	return (0);
}

/*
	dead_monitor check if the philo is dead. It compares the time_to_die with
	the personal last_eat_time, raising the end_flag in case someone didn't
	eat in time.
*/
static int	is_philo_dead(t_monastery *data, int i)
{
	t_philo *philo;

	if (is_end_flag_set(data))
		return (1);
	philo = data->philo + i;
	pthread_mutex_lock(philo->eat_time_lock);
	if (get_rel_time(data->time.clock_start) - philo->last_eat_time > data->time.to_die) // >= OR >????
	{
		pthread_mutex_unlock(philo->eat_time_lock);
		if (!sad_end(data))
			return (1);
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
	int			i;

	data = (t_monastery *)arg;
	i = 0;
	while (1)
	{
		if (is_philo_dead(data, i))
			break ;
		i++;
		if (i == data->n_philo)
		{
			i = 0;
			usleep(450);
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
		if (is_end_flag_set(data))
			break ;
		pthread_mutex_lock(data->meals_locks + i);
		if ((data->philo + i)->n_meals >= data->time.eat_limit)
			n_done++;
		pthread_mutex_unlock(data->meals_locks + i);
		i++;
		if (i == data->n_philo)
		{
			if (n_done == data->n_philo)
			{
				happy_end(data);
				break ;
			}
			n_done = 0;
			i = 0;
			usleep(450);
		}
	}
	return (NULL);
}
