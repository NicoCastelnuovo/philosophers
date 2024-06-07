/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:57:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/12 15:00:09 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_data(t_monastery *data)
{
	data->philo = NULL;
	data->forks = NULL;
	data->eat_time_locks = NULL;
	data->meals_locks = NULL;
}

int	main(int argc, char **argv)
{
	t_monastery	data;

	init_data(&data);
	if (create_monastery(&data, argc, argv))
		return (free_mem(&data), data.err_code);
	if (create_threads(&data))
		return (free_mem(&data), data.err_code);
	if (join_threads(&data))
		return (free_mem(&data), data.err_code);
	if (destroy_mutex(&data))
		return (free_mem(&data), data.err_code);
	free_mem(&data);
	return (0);
}
