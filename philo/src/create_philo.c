/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 08:58:47 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/09 08:42:29 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Assign to each philo the correct forks. Only the first philo has a
	different logic to have assigned the left fork.
	    0   1   2   3   4
	o ¥ o ¥ o ¥ o ¥ o ¥
	  0   1   2   3   4
	the first philo and the right for the last philo.
// */
static void	share_forks(t_philo *philo, pthread_mutex_t *forks, int n_philo)
{
	// if (n_philo == 1)
	if (philo->id == 0) // first philo
		philo->l_fork = forks + (n_philo - 1);
	else
		philo->l_fork = forks + (philo->id - 1);
	philo->r_fork = forks + (philo->id); // right mutex
}

static void	share_locks(t_philo *philo, t_monastery *data)
{
	share_forks(philo, data->forks, data->n_philo);
	philo->print_lock = &data->print_lock;
	philo->eat_lock = data->eat_locks + philo->id;
	philo->dead_lock = &data->dead_lock;
}

static void	parse_philo(int i, t_philo *philo, t_monastery *data)
{
	philo->id = i;
	philo->time = data->time;
	share_locks(philo, data);
	philo->n_eat = 0;
	philo->eat_time = 0;
}

t_philo	**create_philo(t_monastery *data)
{
	t_philo	**philo;
	int		i;

	philo = ft_calloc(data->n_philo + 1, sizeof(t_philo *)); // create + 1 philo ???
	if (!philo)
		return (NULL); // remember to freeee()
	i = 0;
	while (i < data->n_philo)
	{
		philo[i] = ft_calloc(1, sizeof(t_philo));
		if (!philo[i])
			return (NULL); // remember to freeee()
		parse_philo(i, philo[i], data);
		i++;
	}
	return (philo);
}
