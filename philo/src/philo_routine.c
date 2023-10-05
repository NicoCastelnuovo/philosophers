/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:36:27 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/05 09:01:01 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_end(t_philo *philo)
{
	// protect with mutex
	if (philo->time->someone_is_dead || philo->time->everyone_has_eaten)
		return (1);
	return (0);
}

static int	philo_sleep_and_think(t_philo *philo, int64_t clock_start)
{
	print_tmstmp(philo->id, SLEEP, clock_start);
	philo->start_sleeping = now(clock_start);
	accurate_sleep(philo->time->to_sleep);
	if (is_end(philo))
		return (1);
	philo->is_turn = 1;
	print_tmstmp(philo->id, THINK, clock_start);
	philo->start_thinking = now(clock_start);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int64_t	clock_start;

	philo = (t_philo *)arg;
	clock_start = philo->time->clock_start;
	while (1)
	{
		if (is_end(philo))
			break ;
		if (!philo->is_turn)
		{
			if (philo_sleep_and_think(philo, clock_start) != 0)
				break ;
		}
		if (philo->is_turn)
		{
			// take 1st fork and continue thinking
			pthread_mutex_lock(philo->fork[0]);
			if (is_end(philo))
			{
				pthread_mutex_unlock(philo->fork[0]);
				break ;
			}
			print_tmstmp(philo->id, FORK, clock_start);


			// take the 2nd fork and stop think
			pthread_mutex_lock(philo->fork[1]);
			if (is_end(philo))
			{
				pthread_mutex_unlock(philo->fork[0]);
				pthread_mutex_unlock(philo->fork[1]);
				break ;
			}
			print_tmstmp(philo->id, FORK, clock_start);


			// eating
			print_tmstmp(philo->id, EAT, clock_start);
			philo->n_eat += 1;
			philo->is_turn = 0;
			philo->last_eat = now(clock_start); // beginning of the meal
			accurate_sleep(philo->time->to_eat);
			// update n_cycles
			pthread_mutex_unlock(philo->fork[0]);
			pthread_mutex_unlock(philo->fork[1]);
		}
		if (is_end(philo))
			break ;
	}
	return (NULL);
}

// #include "philo.h"

// static int	is_end(t_philo *philo)
// {
// 	// protect with mutex
// 	if (philo->time->someone_is_dead || philo->time->everyone_has_eaten)
// 		return (1);
// 	return (0);
// }

// static int	philo_sleep_and_think(t_philo *philo, int64_t clock_start)
// {
// 	print_tmstmp(philo->id, SLEEP, clock_start);
// 	philo->start_sleeping = now(clock_start);
// 	accurate_sleep(philo->time->to_sleep);
// 	if (is_end(philo))
// 		return (1);
// 	philo->is_turn = 1;
// 	print_tmstmp(philo->id, THINK, clock_start);
// 	philo->start_thinking = now(clock_start);
// 	return (0);
// }

// void	*philo_routine(void *arg)
// {
// 	t_philo	*philo;
// 	int64_t	clock_start;

// 	philo = (t_philo *)arg;
// 	clock_start = philo->time->clock_start;
// 	while (1)
// 	{
// 		if (is_end(philo))
// 			break ;
// 		if (!philo->is_turn)
// 		{
// 			if (philo_sleep_and_think(philo, clock_start) != 0)
// 				break ;
// 		}
// 		if (philo->is_turn)
// 		{
// 			// take 1st fork and continue thinking
// 			pthread_mutex_lock(philo->fork[0]);
// 			if (is_end(philo))
// 			{
// 				pthread_mutex_unlock(philo->fork[0]);
// 				break ;
// 			}
// 			print_tmstmp(philo->id, FORK, clock_start);

// 			// take the 2nd fork and stop think
// 			pthread_mutex_lock(philo->fork[1]);
// 			if (is_end(philo))
// 			{
// 				pthread_mutex_unlock(philo->fork[0]);
// 				pthread_mutex_unlock(philo->fork[1]);
// 				break ;
// 			}
// 			print_tmstmp(philo->id, FORK, clock_start);

// 			// eating
// 			print_tmstmp(philo->id, EAT, clock_start);
// 			philo->n_eat += 1;
// 			philo->is_turn = 0;
// 			philo->last_eat = now(clock_start); // beginning of the meal
// 			accurate_sleep(philo->time->to_eat);
// 			// update n_cycles
// 			pthread_mutex_unlock(philo->fork[0]);
// 			pthread_mutex_unlock(philo->fork[1]);
// 		}
// 		if (is_end(philo))
// 			break ;
// 	}
// 	return (NULL);
// }
