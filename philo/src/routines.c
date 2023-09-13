/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:36:27 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/13 16:21:59 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_philo(t_philo *philo)
{
}

void	*supervision(void *arg)
{
	t_monastery *data;
	int			i;

	data = (t_monastery *)arg;

}

void	*routine(void *arg)
{
	t_philo		*philo;
	long int	start;

	philo = (t_philo *)arg;
	start = philo->time->start;
	while (1)
	{
		if (!philo->is_turn)
		{
			printf("%d %d is sleeping\n", get_time_ms() - start, philo->id);
			better_sleep(philo->time->sleep);
			philo->is_turn = 1;
			// philo starts thinking ???
			philo->start_think = get_time_ms() - start;
			printf("%d %d is thinking\n", get_time_ms() - start, philo->id);
		}
		else if (philo->is_turn)
		{
			// taking fork left
			pthread_mutex_lock(philo->mutex[0]);
			printf("%d %d has taken a fork\n", get_time_ms() - start, philo->id);

			// check if died?

			// stop thinking ???
			// taking fork right
			pthread_mutex_lock(philo->mutex[1]);
			printf("%d %d has taken a fork\n", get_time_ms() - start, philo->id);
			if (philo->start_think)
			{
				philo->end_think = get_time_ms() - start;
				// printf("[ %llums ][ %d ] thought\n", philo->end_think - philo->start_think, philo->id);
			}

			// eating moment
			printf("%d %d is eating\n", get_time_ms() - start, philo->id);
			philo->start_eat = get_time_ms() - start; // beginning of the meal
			better_sleep(philo->time->eat);
			philo->is_turn = 0;

			// finish eating
			philo->n_cycles += 1; // maybe outside the mutex ????
			// philo->start_think = 0; // reset // not necessary
			// philo->end_think = 0;
			// printf("%d %d leaves the forks\n", get_time_ms() - start, philo->id);

			pthread_mutex_unlock(philo->mutex[0]);
			pthread_mutex_unlock(philo->mutex[1]);
		}
	}
	return (NULL);
}
