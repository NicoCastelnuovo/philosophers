/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 08:58:47 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/05 09:46:38 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Divide the total philosophers into 2 groups, group [0] and [1]. The group
	which has [1] can eat. If the total of philo is odd, one philo is "moved"
	to the group which will first sleep.
*/
static int	assign_to_group(int id, int n)
{
	if (n % 2 != 0 && id == n) // odd id
		return (0);
	if (id % 2 == 0) // even id - even ids doesn't start
		return (0);
	return (1);
}

/*
	Assign to each philo the correct forks. philo->fork[0] is the left one and
	philo->fork[1] is the right. Only the first philo has a different logic to
	have assigned the left fork.
	         0   1   2   3   4
	-> [¥] o ¥ o ¥ o ¥ o ¥ o ¥ -> the fork in brackets is the left one for
	       0   1   2   3   4
	the first philo and the right for the last philo.
*/
static void	share_forks(t_philo *philo, pthread_mutex_t *mutex, int n_philo)
{
	// if (n_philo == 1)
	if (philo->id == 0) // first philo
		philo->fork[0] = mutex + (n_philo - 1);
	else
		philo->fork[0] = mutex + (philo->id - 1);
	philo->fork[1] = mutex + (philo->id); // right mutex
}

static void	parse_philo(int i, t_philo *philo, t_monastery *data)
{
	philo->id = i;
	philo->time = data->time;
	share_forks(philo, data->forks, data->n_philo);
	philo->is_turn = assign_to_group(philo->id + 1, data->n_philo);
	philo->n_eat = 0;
	philo->last_eat = 0;
	philo->start_thinking = 0;
	philo->end_thinking = 0;
	philo->start_sleeping = 0;
}

t_philo	**create_philo(t_monastery *data)
{
	t_philo	**philo;
	int		i;

	philo = ft_calloc(data->n_philo + 1, sizeof(t_philo *));
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
