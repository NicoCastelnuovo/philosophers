/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:36:27 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/06 11:06:40 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_end(t_philo *philo)
{

}

static void	philo_think(t_philo *philo)
{
	int64_t	clock_start;

	clock_start = philo->time->clock_start;
	print_tmstmp(philo, THINK, now_us(clock_start));
}

static void	philo_eat(t_philo *philo)
{
	int64_t	clock_start;

	clock_start = philo->time->clock_start;
	print_tmstmp(philo, EAT, now_us(clock_start));
	pthread_mutex_lock(philo->eat_lock);
	philo->eat_time = now_us(clock_start);
	pthread_mutex_unlock(philo->eat_lock);
	accurate_sleep_us(philo->time->to_eat);
}

static int	philo_sleep(t_philo *philo)
{
	int64_t	clock_start;

	clock_start = philo->time->clock_start;
	print_tmstmp(philo, SLEEP, now_us(clock_start));
	accurate_sleep_us(philo->time->to_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int64_t	clock_start;

	philo = (t_philo *)arg;
	clock_start = philo->time->clock_start;
	if (!philo->can_start_eating)	// move outside the while(1) // maybe rename to first_turn
	{
		philo_sleep(philo);
		philo_think(philo);
	}
	while (1)
	{
		pthread_mutex_lock(philo->l_fork);					// either inside philo_eat() or lock_mutexes()
		print_tmstmp(philo, FORK, now_us(clock_start));
		pthread_mutex_lock(philo->r_fork);
		print_tmstmp(philo, FORK, now_us(clock_start));

		philo_eat(philo);
		pthread_mutex_lock(philo->dead_lock);
		if (philo->time->dead_flag)
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->dead_lock);
			break ;
		}
		pthread_mutex_unlock(philo->dead_lock);

		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);

		philo_sleep(philo);
		pthread_mutex_lock(philo->dead_lock);
		if (philo->time->dead_flag)
		{
			pthread_mutex_unlock(philo->dead_lock);
			break ;
		}
		pthread_mutex_unlock(philo->dead_lock);

		philo_think(philo);
	}
	return (NULL);
}
