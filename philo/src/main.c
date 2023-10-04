/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:57:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/04 15:56:36 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_monastery	data;
	int			err_code;

	/*
		err-code solutions:
			1) just use data->err_code
			2) make less number of errors, and make them function-related
	*/

	if (argc < 5 || argc > 6)
		return (error(EARGC, __FILE__, __LINE__));
	err_code = create_monastery(&data, argv); // make err_code an internal to t_monastery
	if (err_code)
		return (err_code);

	// start threads
	err_code = create_threads(&data);
	if (err_code)
		return (err_code);

	err_code = join_threads(&data);
	if (err_code)
		return (err_code);

	int i = 0;
	while (i < data.n_philo)
	{
		if (pthread_mutex_destroy(data.mutex + i) != 0)
			return (error(EDESTROY_MUTEX, __FILE__, __LINE__));
		i++;
	}

	print_all_philo(data.philo);
	return (0);
}
