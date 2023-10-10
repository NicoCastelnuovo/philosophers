/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_monastery.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:46:28 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/10 18:40:58 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_forks(t_monastery *data)
{
	int	i;

	data->forks = ft_calloc(data->n_philo, sizeof(pthread_mutex_t));
	if (!data->forks)
		return (error(&data->err_code, EMALLOC, __FILE__, __LINE__));
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(data->forks + i, NULL) != 0)
			return (error(&data->err_code, EMUTEX_INIT, __FILE__, __LINE__));
		i++;
	}
	return (0);
}

static int	create_locks(t_monastery *data)
{
	int	i;

	if (create_forks(data))
		return (error(&data->err_code, EMUTEX_INIT, __FILE__, __LINE__));

	if (pthread_mutex_init(&data->dead_lock, NULL))
		return (error(&data->err_code, EMUTEX_INIT, __FILE__, __LINE__));

	i = 0;
	data->eat_locks = ft_calloc(data->n_philo, sizeof(pthread_mutex_t));
	if (!data->eat_locks)
		return (error(&data->err_code, EMALLOC, __FILE__, __LINE__));
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(data->eat_locks + i, NULL))
			return (error(&data->err_code, EMUTEX_INIT, __FILE__, __LINE__));
		i++;
	}

	if (pthread_mutex_init(&data->print_lock, NULL))
		return (error(&data->err_code, EMUTEX_INIT, __FILE__, __LINE__));
	return (0);
}

/*
	Check if there is a n times each philo has to eat. If yes, data->n_eat_status
	is created to be monitored by the eat_monitor. Each int * points to a philo's
	n_eat.
*/
static int	parse_eat_limit(t_monastery *data, char **argv)
{
	int	i;

	if (argv[5])
		data->time.eat_limit = ft_atoi(argv[5]); // remove and set to (null) ???
	else
		data->time.eat_limit = -1; // remove if not important - if not present will be 0
	if (data->time.eat_limit > -1)
	{
		data->n_eat_status = ft_calloc(data->n_philo, sizeof(int));
		if (!data->n_eat_status)
			return (error(&data->err_code, EMALLOC, __FILE__, __LINE__));
		i = 0;
		while (i < data->n_philo)
		{
			data->n_eat_status[i] = (data->philo + i)->n_eat;
			i++;
		}
	}
	return (0);
}

// static int	is_valid_input(t_monastery *data)
// {
// 	if (data->n_philo <= 0)
// 		return (1);
// 	if ()
// }

static int	parse_input(t_monastery *data, char **argv)
{
	data->n_philo = ft_atoi(argv[1]);
	data->time.to_die = ft_atoi(argv[2]);
	data->time.to_eat = ft_atoi(argv[3]);
	data->time.to_sleep = ft_atoi(argv[4]);
	data->time.clock_start = 0;
	// eat_limit left
	// if (!is_valid_input(data))
	// 	return (error(&data->err_code, EARGV, __FILE__, __LINE__));
	return (0);
}

int	create_monastery(t_monastery *data, char **argv)
{
	if (parse_input(data, argv))
		return (data->err_code);

	if (create_locks(data))
		return (data->err_code);

	data->dead_flag = 0;

	data->philo = create_philo(data);
	if (!data->philo)
		return (error(&data->err_code, ECREATE_PHILO, __FILE__, __LINE__));

	if (parse_eat_limit(data, argv))
		return (data->err_code);

	return (0);
}
