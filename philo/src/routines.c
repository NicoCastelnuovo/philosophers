/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:36:27 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/12 16:27:58 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*starters(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->mutex[0]);
	pthread_mutex_lock(philo->mutex[1]);
		printf("[%d] has taken a fork.\n", philo->id);
		sleep(1); // usleep(philo->time->eat);
		printf("Fork[0] is [%d]\n", *(philo->fork[0]));
		printf("Fork[1] is [%d]\n", *(philo->fork[1]));
		*(philo->fork[0]) += 1;
		*(philo->fork[1]) += 1;
		philo->n_cycles += 1;
	pthread_mutex_unlock(philo->mutex[0]);
	pthread_mutex_unlock(philo->mutex[1]);
	return (NULL);
}

/*
	if executed now, with example (n) 410 200 200, then every fork is used
	two times each, and each philo eat exactly one time.
*/

void	*queued(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->mutex[0]);
	pthread_mutex_lock(philo->mutex[1]);
		printf("[%d] has taken a fork.\n", philo->id);
		sleep(1); // usleep(philo->time->eat);
		printf("Fork[0] is [%d]\n", *(philo->fork[0]));
		printf("Fork[1] is [%d]\n", *(philo->fork[1]));
		*(philo->fork[0]) += 1;
		*(philo->fork[1]) += 1;
		philo->n_cycles += 1;
	pthread_mutex_unlock(philo->mutex[0]);
	pthread_mutex_unlock(philo->mutex[1]);
	return (NULL);
}
