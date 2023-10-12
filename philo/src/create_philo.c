/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 08:58:47 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/12 15:06:07 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Assign each philo the correct left and right fork. If the n_philo is 1,
	he will try to take both forks, but he will find the same one, so that
	philo->l_fork == philo->r_fork.
*/
static void	share_forks(t_philo *philo, pthread_mutex_t *forks, int n_philo)
{
	if (philo->id == 0)
		philo->l_fork = forks + (n_philo - 1);
	else
		philo->l_fork = forks + (philo->id - 1);
	philo->r_fork = forks + (philo->id);
}

static void	share_locks(t_philo *philo, t_monastery *data)
{
	share_forks(philo, data->forks, data->n_philo);
	philo->print_lock = &data->print_lock;
	philo->eat_time_lock = data->eat_time_locks + philo->id;
	philo->meals_lock = data->meals_locks + philo->id;
	philo->end_lock = &data->end_lock;
}

static void	parse_philo(int i, t_philo *philo, t_monastery *data)
{
	t_philo	*current_philo;

	current_philo = philo + i;
	current_philo->id = i;
	current_philo->time = &data->time;
	share_locks(current_philo, data);
	current_philo->n_meals = 0;
	current_philo->last_eat_time = 0;
	current_philo->end_flag = &data->end_flag;
}

t_philo	*create_philo(t_monastery *data)
{
	t_philo	*philo;
	int		i;

	philo = ft_calloc(data->n_philo, sizeof(t_philo));
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->n_philo)
	{
		parse_philo(i, philo, data);
		i++;
	}
	return (philo);
}
