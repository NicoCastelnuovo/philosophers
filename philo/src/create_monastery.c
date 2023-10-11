/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_monastery.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:46:28 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/11 15:06:17 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	init_mutex(pthread_mutex_t *mutex, int *err_store)
// {
// 	if (pthread_mutex_init(mutex, NULL))
// 		return (error(err_store, EMUTEX_INIT));
// 	return (0);
// }

static int	create_forks(t_monastery *data)
{
	int	i;

	data->forks = ft_calloc(data->n_philo, sizeof(pthread_mutex_t));
	if (!data->forks)
		return (error(&data->err_code, EMALLOC));
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(data->forks + i, NULL) != 0)
			return (error(&data->err_code, EMUTEX_INIT));
		i++;
	}
	return (0);
}

static int	create_locks(t_monastery *data)
{
	int		i;

	if (create_forks(data))
		return (error(&data->err_code, EMUTEX_INIT));
	if (pthread_mutex_init(&data->end_lock, NULL))
		return (error(&data->err_code, EMUTEX_INIT));
	i = 0;
	data->eat_time_locks = ft_calloc(data->n_philo, sizeof(pthread_mutex_t));
	if (!data->eat_time_locks)
		return (error(&data->err_code, EMALLOC));
	data->meals_locks = ft_calloc(data->n_philo, sizeof(pthread_mutex_t));
	if (!data->meals_locks)
		return (error(&data->err_code, EMALLOC));
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(data->eat_time_locks + i, NULL))
			return (error(&data->err_code, EMUTEX_INIT));
		if (pthread_mutex_init(data->meals_locks + i, NULL))
			return (error(&data->err_code, EMUTEX_INIT));
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (error(&data->err_code, EMUTEX_INIT));
	return (0);
}

static int	is_valid_input(char **argv)
{
	int	i;

	i = 1;
	while (i < 4)
	{
		if (ft_atol(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

static void	set_ttable(t_monastery *data, char **argv)
{
	data->time.to_die = ft_atol(argv[2]);
	data->time.to_eat = ft_atol(argv[3]);
	data->time.to_sleep = ft_atol(argv[4]);
	data->time.eat_limit = 0;
	if (argv[5])
		data->time.eat_limit = ft_atol(argv[5]);
	data->time.to_think = 0;
	if (data->n_philo % 2)
		data->time.to_think = 1;
	data->time.clock_start = 0;
}

int	create_monastery(t_monastery *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error(&data->err_code, EARG));
	data->n_philo = ft_atol(argv[1]);
	if (!is_valid_input(argv))
		return (error(&data->err_code, EARG));
	set_ttable(data, argv);
	if (create_locks(data))
		return (data->err_code);
	data->philo = create_philo(data);
	if (!data->philo)
		return (error(&data->err_code, ECREATE_PHILO));
	data->end_flag = 0;
	return (0);
}
