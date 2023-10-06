/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 08:58:47 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/06 10:29:59 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Philo whose (id + 1) is even, will start to eat and pick the left fork.
	The odd philo, start sleeping, and pick always the right one.
	Divide the total philosophers into 2 groups. The group whose (id + 1) is
	even will start.
*/
static int	is_starting_group(int id)
{
	if (id % 2 != 0) // ODD will start
		return (1);
	return (0); // EVEN
}

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
	philo->can_start_eating = is_starting_group(philo->id);
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
