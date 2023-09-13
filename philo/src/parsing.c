/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:46:28 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/13 17:37:43 by ncasteln         ###   ########.fr       */
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
	if (n % 2 != 0 && id == n)
		return (0);
	if (id % 2 == 0)
		return (0);
	else
		return (1);
}

static void	*share_forks(t_philo *philo, int *forks, int n_philo)
{
	int	i;

	i = philo->id - 1;
	if (i == 0) // first philo
		philo->fork[0] = forks + (n_philo - 1);
	else
		philo->fork[0] = forks + (i - 1);
	philo->fork[1] = forks + i;
}

static void	*share_mutex(t_philo *philo, pthread_mutex_t *mutex, int n)
{
	int	i;

	i = philo->id - 1;
	if (i == 0) // first philo
		philo->mutex[0] = mutex + (n - 1);
	else
		philo->mutex[0] = mutex + (i - 1);
	philo->mutex[1] = mutex + i; // right mutex
}

static void	parse_philo(int i, t_philo *philo, t_monastery *data)
{
	philo->id = i + 1;
	philo->time = data->time;// just want info, not modify the values -- err prone ?
	share_forks(philo, data->forks, data->n_philo);
	share_mutex(philo, data->mutex, data->n_philo);
	philo->is_turn = assign_to_group(philo->id, data->n_philo);
	philo->n_cycles = 0;
	philo->start_eat = 0; // /????
	philo->start_think = 0; // /????
	philo->end_think = 0; // /????
}

static t_philo	**create_philo(t_monastery *data)
{
	t_philo	**philo;
	int		i;

	philo = ft_calloc(data->n_philo + 1, sizeof(t_philo *)); // set +1 as size???
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

int	parse_monastery(t_monastery *data, char **argv)
{
	int	i;

	// PHILO NUMBER
	data->n_philo = ft_atoi(argv[1]);

	// MUTEXES
	data->mutex = ft_calloc(data->n_philo, sizeof(pthread_mutex_t));
	if (!data->mutex)
		return (error(EMALLOC, __FILE__, __LINE__));
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(data->mutex + i, NULL))
			return (error(EMUTEX, __FILE__, __LINE__));
		i++;
	}

	// TIMESTAMP
	data->time = ft_calloc(1, sizeof(t_time));
	if (!data->time)
		return (error(EMALLOC, __FILE__, __LINE__));
	data->time->health = ft_atoi(argv[2]); //* 1000;
	data->time->eat = ft_atoi(argv[3]); //* 1000;
	data->time->sleep = ft_atoi(argv[4]); //* 1000;
	if (argv[5])
		data->time->limit = ft_atoi(argv[5]);
	else
		data->time->limit = 0; // remove if not important
	data->time->start = 0;


	// FORKS
	data->forks = ft_calloc(data->n_philo, sizeof(int));
	if (!data->forks)
		return (error(EMALLOC, __FILE__, __LINE__));
	i = 0;
	while (i < data->n_philo)
	{
		data->forks[i] = 0; // ------------- giving an id to the forks just to recognize!
		i++;
	}

	// PHILOSOPHERS
	data->philo = create_philo(data);
	if (!data->philo)
		return (error(ECREATE_PHILO, __FILE__, __LINE__));

	// THREADS
	data->th = ft_calloc(data->n_philo + 1, sizeof(pthread_t));
	if (!data->th)
		return (error(EMALLOC, __FILE__, __LINE__));

	return (0);
}
