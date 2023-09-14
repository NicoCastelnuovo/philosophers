/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:36:27 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/14 13:49:34 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	The supevisor check if the philo is dead. It compares the time_to_die with
	the moment in which the philo went to sleep or began to eat. If those
	interval are equal to time_to_die, means that philo died.
*/
static int	is_philo_dead(t_philo *philo)
{
	t_time	*time;

	time = philo->time;
	if (philo->end_thinking)
	{
		// still necessary to point out when die while sleeping? ----> [[YES]] --> 4 310 200 100
		if (now(time->clock_start) - philo->start_sleeping >= time->to_die)
		{
			// printf("philo[%d] died while sleeping [ %llums ]\n", philo->id, now(time->clock_start) - philo->start_sleeping);
			return (1);
		}
		if (now(time->clock_start) - philo->last_eat >= time->to_die)
		{
			// printf("philo[%d] don't eat for [ %llums ]\n", philo->id, now(time->clock_start) - philo->last_eat);
			return (1);
		}
	}
	return (0);
}

void	*supervision(void *arg)
{
	t_monastery	*data;
	t_philo		**philo;
	int64_t		clock_start;
	int			i;

	data = (t_monastery *)arg;
	clock_start = data->time->clock_start;
	philo = data->philo;
	i = 0;
	while (philo[i])
	{
		if (is_philo_dead(philo[i]))
		{
			data->time->is_end = 1;
			print_tmstmp(philo[i]->id, DIE, clock_start);
			break ;
		}
		i++;
		if (i == data->n_philo)
			i = 0;
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int64_t	clock_start;

	philo = (t_philo *)arg;
	clock_start = philo->time->clock_start;
	while (1)
	{
		if (philo->time->is_end)
			break ;
		if (!philo->is_turn)
		{
			print_tmstmp(philo->id, SLEEP, clock_start);
			philo->start_sleeping = now(clock_start);
			better_sleep(philo->time->to_sleep);
			// philo->end_sleeping = now(clock_start);
			if (philo->time->is_end)
				break ;
			philo->is_turn = 1;
			philo->start_thinking = now(clock_start);
			print_tmstmp(philo->id, THINK, clock_start);
		}
		else if (philo->is_turn)
		{
			// take 1st fork and continue thinking
			pthread_mutex_lock(philo->mutex[0]);
			if (philo->time->is_end)
				break ;
			print_tmstmp(philo->id, FORK, clock_start);
			// take the 2nd fork and stop think
			pthread_mutex_lock(philo->mutex[1]);
			if (philo->time->is_end)
				break ;
			print_tmstmp(philo->id, FORK, clock_start);
			if (philo->start_thinking)
			{
				philo->end_thinking = now(clock_start);
				if (philo->time->is_end)
				{
					pthread_mutex_unlock(philo->mutex[0]);
					pthread_mutex_unlock(philo->mutex[1]);
					break ;
				}
			}

			// eating
			print_tmstmp(philo->id, EAT, clock_start);
			philo->is_turn = 0;
			philo->n_cycles += 1;												// maybe outside the mutex ????
			philo->last_eat = now(clock_start); // beginning of the meal
			better_sleep(philo->time->to_eat);
			pthread_mutex_unlock(philo->mutex[0]);
			pthread_mutex_unlock(philo->mutex[1]);
		}
		if (philo->time->is_end)
			break ;
	}
	// printf("	philo[%d] break @ [ %llu ]\n", philo->id, now(clock_start));
	return (NULL);
}
