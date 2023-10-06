/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:57:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/06 11:42:23 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_monastery	data;

	data.err_code = 0;
	if (argc < 5 || argc > 6)
		return (error(&data.err_code, EARGC, __FILE__, __LINE__));
	if (create_monastery(&data, argv))
		return (data.err_code);
	if (create_threads(&data))
		return (data.err_code);
	if (join_threads(&data))
		return (data.err_code);
	int i = 0;
	while (i < data.n_philo)
	{
		if (pthread_mutex_destroy(data.forks + i) != 0)
			return (error(&data.err_code, EMUTEX_DESTROY, __FILE__, __LINE__));
		i++;
	}
	return (0);
}
