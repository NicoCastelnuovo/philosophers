/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:27:25 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/04 11:32:36 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	dead_monitor check if the philo is dead. It compares the time_to_die with
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

void	*dead_routine(void *arg)
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
			data->time->someone_is_dead = 1;
			print_tmstmp(philo[i]->id, DIE, clock_start);
			break ;
		}
		i++;
		if (i == data->n_philo)
			i = 0;
	}
}

/*
	eat_monitor modifies data->n_eat_status, synchronizing it with each philo's n_eat.
	In case someone raches the data->time->eat_limit, the value is set to -1 as an
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
}
