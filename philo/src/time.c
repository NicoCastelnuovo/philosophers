/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:50:19 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/13 17:07:17 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	struct timeval
		time_t		tv_sec;		>> seconds since Jan. 1, 1970
		suseconds_t	tv_usec;	>> and microseconds
*/
uint64_t	get_time_ms(void)
{
	struct timeval	t;
	uint64_t		s_to_ms;
	uint64_t		u_to_ms;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	s_to_ms = t.tv_sec * 1000;
	u_to_ms = t.tv_usec / 1000;
	return (s_to_ms + u_to_ms);
}

uint64_t	get_time_us(void)
{
	struct timeval	t;
	uint64_t		s_to_us;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	s_to_us = t.tv_sec * 1000000;
	return (s_to_us + t.tv_usec);
}

void	better_sleep(uint64_t n)
{
	uint64_t	now = get_time_ms();
	uint64_t	counter = get_time_ms();
	// printf("%llu\n", counter);
	while (counter - now < n) // 400
	{
		usleep(10); // instead of 400000 sleep 10 * (counter - now)
		counter = get_time_ms();
		// printf("[ %llu ] ", counter);
	}
	// printf("%llu\n", counter);
}
