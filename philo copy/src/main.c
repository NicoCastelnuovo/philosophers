/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:57:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/12 08:21:34 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*share_forks(t_philo *philo, int *forks, int n_philo)
{
	int	i;

	i = philo->id - 1;
	if (i == 0) // first philo
	{
		philo->r_fork = forks;
		philo->l_fork = forks + (n_philo - 1);
	}
	else if (i == (n_philo - 1)) // last philo
	{
		philo->r_fork = forks + (n_philo - 1);
		philo->l_fork = forks + (n_philo - 2);
	}
	else // mid philo
	{
		philo->r_fork = forks + i;
		philo->l_fork = forks + (i - 1);
	}
}

static void	parse_philo(int id, t_philo *philo, t_monastery *data, char **argv)
{
	// init_philo(philo);
	philo->id = id;
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->end = ft_atoi(argv[5]);
	share_forks(philo, data->forks, data->n_philo);
	// philo->mutex = data->mutex;
	philo->mutex = &(data->mutex);
}

/* Populate the monastry with correct number of philo */
static t_philo	**create_philosophers(t_monastery *data, char **argv)
{
	t_philo	**philo;
	int		i;

	philo = NULL;
	philo = ft_calloc(data->n_philo + 1, sizeof(t_philo *)); // set +1 as size???
	if (!philo)
		return (NULL); // remember to freeee()
	i = 0;
	while (i < data->n_philo)
	{
		philo[i] = ft_calloc(1, sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		parse_philo(i + 1, philo[i], data, argv);
		i++;
	}
	return (philo);
}

void	*ROUT(void *N)
{
	sleep(3);
	int *M = (int *)N;
	printf("{{{%d}}}\n", *M);
}

static int	parse_monastery(t_monastery *data, char **argv)
{
	int				i;
	// pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex;

	// mutex = ft_calloc(1, sizeof(pthread_mutex_t));
	// if (pthread_mutex_init(&mutex, NULL))
	if (pthread_mutex_init(&data->mutex, NULL))
		return (EMUTEX);
	// data->mutex = mutex;
	data->mutex = mutex;

	data->n_philo = ft_atoi(argv[1]);
	data->th = ft_calloc(data->n_philo + 1, sizeof(pthread_t));
	if (!data->th)
		return (error(EMALLOC, __FILE__, __LINE__));
	// th[data->n_philo] = NULL;

	data->forks = ft_calloc(data->n_philo, sizeof(int));
	if (!data->forks)
		return (error(EMALLOC, __FILE__, __LINE__));
	i = 0;
	while (i < data->n_philo)
	{
		data->forks[i] = i; // giving an id to the forks!
		i++;
	}

	data->philo = create_philosophers(data, argv);
	if (!data->philo)
		return (error(ECREATE_PHILO, __FILE__, __LINE__));


	// int	N = 8;
	// data->philo[0]->n = &N;
	// printf("The address [%p]\n", &N);
	// pthread_t TH;
	// pthread_create(&TH, NULL, &ROUT, &N);
	// sleep(2);


	return (0);
}

int	main(int argc, char **argv)
{
	t_monastery	data;
	int			err_code;

	if (argc < 5 || argc > 6)
		return (error(EARGC, __FILE__, __LINE__));
	err_code = parse_monastery(&data, argv);

	// int	N = 8;
	// data.philo[0]->n = &N;
	// printf("The address [%p]\n", data.philo[0]->n);

	if (err_code)
		return (err_code);
	err_code = create_threads(&data);
	if (err_code)
		return (err_code);
	err_code = join_threads(&data);
	if (err_code)
		return (err_code);
	return (0);
}
