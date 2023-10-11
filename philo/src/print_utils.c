/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 09:05:42 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/11 14:34:15 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_single_philo(t_philo *philo)
{
	if (!philo)
		return ;
	printf("__PHILO [%d]____", philo->id + 1);
	printf("%d ", philo->time->to_die);
	printf("%d ", philo->time->to_eat);
	printf("%d ", philo->time->to_sleep);
	printf("%d____", philo->time->eat_limit);
	printf("n_eat: [%d]\n", philo->n_meals);
}

void	print_all_philo(t_monastery *data)
{
	int	i;

	if (!data->philo)
		return ;
	i = 0;
	while (i < data->n_philo)
	{
		print_single_philo(data->philo + i);
		i++;
	}
}

void	print_tmstmp(t_philo *philo, t_action what, int64_t when)
{
	int	who;

	who = philo->id + 1;
	pthread_mutex_lock(philo->end_lock);
	if (*(philo->end_flag) == 0)
	{
		pthread_mutex_lock(philo->print_lock);
		if (what == FORK)
			printf("%llu %d has taken a fork\n", when, who);
		else if (what == EAT)
			printf("%llu %d is eating\n", when, who);
		else if (what == SLEEP)
			printf("%llu %d is sleeping\n", when, who);
		else if (what == THINK)
			printf("%llu %d is thinking\n", when, who);
		pthread_mutex_unlock(philo->print_lock);
	}
	pthread_mutex_unlock(philo->end_lock);
}
