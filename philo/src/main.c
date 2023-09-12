/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:57:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/12 15:55:49 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_monastery	data;
	int			err_code;

	if (argc < 5 || argc > 6)
		return (error(EARGC, __FILE__, __LINE__));
	err_code = parse_monastery(&data, argv); // make err_code an internal to t_monastery
	if (err_code)
		return (err_code);
	print_philo(data.philo[0]);
	print_philo(data.philo[1]);
	print_philo(data.philo[2]);
	print_philo(data.philo[3]);
	print_philo(data.philo[4]);

	// align start time
	data.time->start = get_ms();

	// start threads
	err_code = create_threads(&data);
	if (err_code)
		return (err_code);

	err_code = join_threads(&data);
	if (err_code)
		return (err_code);
	return (0);
}
