/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:36:27 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/12 13:03:52 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	n_forks is necessary to unlock the mutex/forks properly in case of the
	end_flag is raised up by the monitors. When n_forks equal to one, it
	corresponds to the case n_philo == 1.
*/
static int	is_end(t_philo *philo, int n_forks)
{
	pthread_mutex_lock(philo->end_lock);
	if (*(philo->end_flag))
	{
		pthread_mutex_unlock(philo->end_lock);
		if (n_forks == 2)
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
		}
		else if (n_forks == 1)
			pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	pthread_mutex_unlock(philo->end_lock);
	return (0);
}

/*
	THe philo take first a different fork, based on their id. Id starts from 0
	to (n_philo - 1), and it's incremented just for the timestamp printing,
	just because the subject states it.
	@stmnt if (philo->l_fork == philo->r_fork) - the case happens only if there
	is one philo. He looks for the left and the right fork, but at the end
	they're the same. This case return (1).
*/
static int	pick_forks(t_philo *philo)
{
	int64_t	clock_start;

	clock_start = philo->time->clock_start;
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_tmstmp(philo, FORK, get_rel_time(clock_start));
		pthread_mutex_lock(philo->l_fork);
		print_tmstmp(philo, FORK, get_rel_time(clock_start));
	}
	else
	{
		if (philo->l_fork == philo->r_fork)
		{
			pthread_mutex_lock(philo->l_fork);
			print_tmstmp(philo, FORK, get_rel_time(clock_start));
			accurate_sleep_ms(philo->time->to_die + 10, clock_start);
			return (1);
		}
		pthread_mutex_lock(philo->l_fork);
		print_tmstmp(philo, FORK, get_rel_time(clock_start));
		pthread_mutex_lock(philo->r_fork);
		print_tmstmp(philo, FORK, get_rel_time(clock_start));
	}
	return (0);
}

static void	philo_eat(t_philo *philo)
{
	int64_t	clock_start;

	clock_start = philo->time->clock_start;
	print_tmstmp(philo, EAT, get_rel_time(clock_start));
	pthread_mutex_lock(philo->eat_time_lock);
	philo->last_eat_time = get_rel_time(clock_start);
	pthread_mutex_unlock(philo->eat_time_lock);
	accurate_sleep_ms(philo->time->to_eat, clock_start);
	pthread_mutex_lock(philo->meals_lock);
	philo->n_meals++;
	pthread_mutex_unlock(philo->meals_lock);
}

/*
	If n_philo is odd, each one is forced to think for 1ms, to let the philo
	with the oldest last_eat_time to pick the fork first.
*/
static void	philo_sleep_and_think(t_philo *philo)
{
	int64_t	clock_start;

	clock_start = philo->time->clock_start;
	print_tmstmp(philo, SLEEP, get_rel_time(clock_start));
	accurate_sleep_ms(philo->time->to_sleep, clock_start);
	print_tmstmp(philo, THINK, get_rel_time(clock_start));
	if (philo->n_meals < 5)
		accurate_sleep_ms(philo->time->to_think, clock_start);
}

/*
	@stmnt if (pick_forks(philo) == 1) - returns (1) just when the philo is
	only one, and that because he can take just one fork.
*/
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (pick_forks(philo) == 1)
		{
			if (is_end(philo, 1))
				break ;
		}
		philo_eat(philo);
		if (is_end(philo, 2))
			break ;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		philo_sleep_and_think(philo);
		if (is_end(philo, 0))
			break ;
	}
	return (NULL);
}
