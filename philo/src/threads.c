/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:40:28 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/12 16:26:04 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_threads(t_monastery *data)
{
	int	i;
	int	err_code;

	i = 0;
	err_code = 0;
	while (i < data->n_philo)
	{
		if (data->philo[i]->is_turn == 1)
		{
			if (pthread_create(data->th + i, NULL, starters, data->philo[i]))
				return (error(ECREATE_THREAD, __FILE__, __LINE__));
		}
		else if (data->philo[i]->is_turn == 0)
			if (pthread_create(data->th + i, NULL, queued, data->philo[i]))
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
