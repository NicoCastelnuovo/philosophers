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

int	is_end_flag_set(t_monastery *data)
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
	is_sad_end() returns (1) only if the flag is set by the death_monitor. In
	case the flag was raised up before it from the meal_monitor, it returns (0)
	so that no dead message is printed.
*/
static int	is_sad_end(t_monastery *data)
{
	pthread_mutex_lock(&data->end_lock);
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

/*
	dead_monitor check if the philo is dead. It compares the time_to_die with
	the personal last_eat_time, raising the end_flag in case someone didn't
	eat in time.
*/
static int	is_philo_dead(t_monastery *data, int i)
{
	t_philo	*philo;
	int64_t	gap_to_check;

	if (is_end_flag_set(data))
		return (1);
	philo = data->philo + i;
	pthread_mutex_lock(philo->eat_time_lock);
	gap_to_check = get_rel_time(data->time.clock_start) - philo->last_eat_time;
	if (gap_to_check > data->time.to_die)
	{
		pthread_mutex_unlock(philo->eat_time_lock);
		if (!is_sad_end(data))
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
