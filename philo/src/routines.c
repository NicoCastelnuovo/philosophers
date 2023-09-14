/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:36:27 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/14 15:26:21 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
	The supervisor returns (1) if a certain philo has eaten at least eat_limit
	number of meals, otherwise (0);
*/
// static int	has_eaten_enough(t_philo *philo)
// {
// 	if (philo->n_cycles == philo->time->eat_limit) // ----- PROBLEM! returns (1) too many times
// 		return (1);
// 	return (0);
// }

// static int	is_philo_done(t_monastery *data)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (data->philo[i]) // stops to NULL
// 	{
// 		j = data->n_philo - 1;
// 		while (j >= 0)
// 		{
// 			if (data->philo[j]->id == data->n_eat[j])
// 			{
// 				if (data->philo[j]->n_cycles == data->time->eat_limit)
// 					data->n_eat[j] = -1;
// 				return (1); // philo now is done, so increment counter
// 			}
// 			j--;
// 		}
// 		i++;
// 	}
// 	return (0); // if reachs end of func, philo probably was already done
// }




/*
	The supevisor check if the philo is dead. It compares the time_to_die with
	the moment in which the philo went to sleep or began to eat. If those
	interval are equal to time_to_die, means that philo died.
*/
static int	is_philo_dead(t_philo *philo)
{
	t_time	*time;

	time = philo->time;

	// !!!!!   SHOULD ADD ALSO THINK + SLEEP TIME ????   !!!!!! ----> seems not

	// if (philo->end_thinking) // is this flag necessary ???????? ----> seems not
	// {

	if (now(time->clock_start) - philo->start_thinking >= time->to_die)
	{
		// printf("philo[%d] died while thinking [ %llums ]\n", philo->id, now(time->clock_start) - philo->start_sleeping);
		return (1);
	}
	if (now(time->clock_start) - philo->start_sleeping >= time->to_die) // still necessary to point out when die while sleeping ??? ----> [[ YES ]] --> 4 310 200 100
	{
		// printf("philo[%d] died while sleeping [ %llums ]\n", philo->id, now(time->clock_start) - philo->start_sleeping);
		return (1);
	}
	if (now(time->clock_start) - philo->last_eat >= time->to_die)
	{
		// printf("philo[%d] don't eat for [ %llums ]\n", philo->id, now(time->clock_start) - philo->last_eat);
		return (1);
	}
	// }
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
		// if (is_philo_done(data))
		// {
		//		// remove it
		//		// data->eat_counter += 1;
		// 		if (data->eat_counter == data->time->limiter)
		//			// break
		// }
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


			// if (philo->start_thinking) // ----------------- necessary this AND end_thinking ?????
			// {
			// 	philo->end_thinking = now(clock_start); // ----------------- necessary this AND end_thinking ?????
			// 	// if (philo->time->is_end) // ----------------- necessary this AND end_thinking ?????
			// 	// {
			// 	// 	pthread_mutex_unlock(philo->mutex[0]);
			// 	// 	pthread_mutex_unlock(philo->mutex[1]);
			// 	// 	break ;
			// 	// }
			// }

			// eating
			print_tmstmp(philo->id, EAT, clock_start);
			philo->is_turn = 0;
			philo->last_eat = now(clock_start); // beginning of the meal
			better_sleep(philo->time->to_eat);
			// update n_cycles
			pthread_mutex_unlock(philo->mutex[0]);
			pthread_mutex_unlock(philo->mutex[1]);
		}
		if (philo->time->is_end)
			break ;
	}
	// printf("	philo[%d] break @ [ %llu ]\n", philo->id, now(clock_start));
	return (NULL);
}
