/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:57:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/14 14:37:56 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_monastery	data;
	int			err_code;

	if (argc < 5 || argc > 6)
		return (error(EARGC, __FILE__, __LINE__));
	err_code = create_monastery(&data, argv); // make err_code an internal to t_monastery
	if (err_code)
		return (err_code);
	// print_all_philo(data.philo); // remove

	// start threads
	err_code = create_threads(&data);
	if (err_code)
		return (err_code);

	err_code = join_threads(&data);
	if (err_code)
		return (err_code);
	pthread_join(data.master, NULL);

	print_all_philo(data.philo);
	return (0);
}
