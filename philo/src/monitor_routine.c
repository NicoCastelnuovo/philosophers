/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:27:25 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/10 15:50:22 by ncasteln         ###   ########.fr       */
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

	philo = data->philo + i;
	pthread_mutex_lock(philo->eat_lock);
	if (get_rel_time(data->time.clock_start) - philo->last_eat_time > data->time.to_die) // ????
	{
		pthread_mutex_unlock(philo->eat_lock);
		pthread_mutex_lock(&data->dead_lock);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead_lock);

		pthread_mutex_lock(&data->print_lock);
		printf("%llu %d died\n", get_rel_time(data->time.clock_start), i + 1);
		pthread_mutex_unlock(&data->print_lock);

		return (1);
	}
	pthread_mutex_unlock(philo->eat_lock);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_monastery	*data;
	t_philo		*philo;
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

/*
	eat_monitor modifies data->n_eat_status, synchronizing it with each philo's n_eat.
	In case someone raches the data->time->eat_limit, the value iss set to -1 as an
	end flag.
*/
void	*eat_routine(void *arg)
{
	// t_monastery	*data;
	// int			i;
	// int			n_done;

	// data = (t_monastery *) arg;
	// i = 0;
	// n_done = 0;
	// while (data->philo[i]) // maybe simplify between this and next statement
	// {
	// 	if (data->n_eat_status[i] > -1) // means: if the philo has not already end to eat
	// 	{
	// 		if (data->philo[i]->n_eat >= data->time->eat_limit) // >= ???
	// 		{
	// 			data->n_eat_status[i] = -1;
	// 			n_done += 1;
	// 		}
	// 		else
	// 			data->n_eat_status[i] = data->philo[i]->n_eat;
	// 	}
	// 	if (n_done == data->n_philo)
	// 	{
	// 		data->time->everyone_has_eaten = 1;
	// 		break ;
	// 	}
	// 	i++;
	// 	if (i == data->n_philo)
	// 		i = 0;
	// }
	return (NULL);
}
