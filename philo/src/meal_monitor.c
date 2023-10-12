/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:53:56 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/12 12:55:58 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	is maybe_happy_end, because it can be that the mutex was locked by
	the other monitor, and when unlocked someone was already dead. But
	if not, it is an happy end!
*/
static void	*maybe_happy_end(t_monastery *data)
{
	pthread_mutex_lock(&data->end_lock);
	if (!data->end_flag)
		data->end_flag = 1;
	pthread_mutex_unlock(&data->end_lock);
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
		if (++i == data->n_philo)
		{
			if (n_done == data->n_philo)
				return (maybe_happy_end(data));
			n_done = 0;
			i = 0;
			usleep(450);
		}
	}
	return (NULL);
}
