/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:00:05 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/11 11:14:42 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t len, size_t n_bits)
{
	char	*p;
	size_t	total_size;

	total_size = len * n_bits;
	if (len && (total_size / len) != n_bits)
		return (NULL);
	p = malloc (total_size);
	if (!p)
		return (NULL);
	memset(p, 0, total_size);
	return (p);
}

void	free_mem(t_monastery *data)
{
	if (data->philo)
		free(data->philo);
	if (data->forks)
		free(data->forks);
	if (data->eat_time_locks)
		free(data->eat_time_locks);
	if (data->meals_locks)
		free(data->meals_locks);
}
