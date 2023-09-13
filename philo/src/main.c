/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:57:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/13 17:11:21 by ncasteln         ###   ########.fr       */
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

	// print_all_philo(data.philo); // remove

	// align start time
	data.time->start = get_time_ms();
	if (!data.time->start)
		return (error(EGET_TIME, __FILE__, __LINE__));
	printf("Start time @ [%llu]\n", data.time->start);

	// better_sleep(400);			// for ms
	// better_sleep(400000);		// for us
	// exit(1);

	// start threads
	err_code = create_threads(&data);
	if (err_code)
		return (err_code);


	err_code = join_threads(&data);
	if (err_code)
		return (err_code);
	pthread_join(data.master, NULL);

	print_all_philo(data.philo); // remove
	return (0);
}

/*
	In order to change time alignment:
	1) line 29 main() --- data.time->start = get_time_us();		// set a us starting time
	2) line 34 main() --- just uncomment the needed function as example if needed
	3) line 110-113 parsing() --- get the arguments from cli and transform in us
	4) better_sleep() --- the functions need to be modified:
			- change get_time_ms() to us()
			- usleep(10) probably remain the same
	5) rountines() --- get-time_ms() modify to us() AND, to see the ms divide it by 1000
*/
