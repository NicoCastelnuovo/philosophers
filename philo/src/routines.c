/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:36:27 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/12 15:49:59 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*starters(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->mutex[0]);
	pthread_mutex_lock(philo->mutex[1]);
		printf("[%d] uses the fork for 2 seconds each...\n", philo->id);
		sleep(1);
		printf("Fork[0] is [%d]\n", *(philo->fork[0]));
		printf("Fork[1] is [%d]\n", *(philo->fork[1]));
		*(philo->fork[0]) += 1;
		*(philo->fork[1]) += 1;
	pthread_mutex_unlock(philo->mutex[0]);
	pthread_mutex_unlock(philo->mutex[1]);
	return (NULL);
}

void	*queued(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	usleep(philo->time->sleep);
	pthread_mutex_lock(philo->mutex[0]);
	pthread_mutex_lock(philo->mutex[1]);
		printf("[%d] uses the fork for 2 seconds each...\n", philo->id);
		sleep(1);
		printf("Fork[0] is [%d]\n", *(philo->fork[0]));
		printf("Fork[1] is [%d]\n", *(philo->fork[1]));
		*(philo->fork[0]) += 1;
		*(philo->fork[1]) += 1;
	pthread_mutex_unlock(philo->mutex[0]);
	pthread_mutex_unlock(philo->mutex[1]);
	return (NULL);
}
