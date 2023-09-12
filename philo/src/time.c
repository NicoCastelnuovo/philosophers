/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:50:19 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/12 12:38:58 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	struct timeval
		time_t		tv_sec;		>> seconds since Jan. 1, 1970
		suseconds_t	tv_usec;	>> and microseconds
*/
long int	get_ms(void)
{
	struct timeval	t;
	long int		s_to_ms;
	long int		u_to_ms;

	if (gettimeofday(&t, NULL) == -1)
		return (1);
	s_to_ms = t.tv_sec * 1000;
	u_to_ms = t.tv_usec / 1000;
	return (s_to_ms + u_to_ms);
}

long int	get_us(void)
{
	struct timeval	t;
	long int		s_to_us;

	if (gettimeofday(&t, NULL) == -1)
		return (1);
	s_to_us = t.tv_sec * 1000000;
	return (s_to_us + t.tv_usec);
}


// int	t1 = get_ms();
// usleep(2000000);
// int	t2 = get_ms();
// printf("t1 ms [%llu]\n", t1);
// printf("t2 ms [%llu]\n", t2);
// printf("Time diff in { ms } [%llu]\n", t2 - t1);

// int	t3 = get_us();
// usleep(2000000);
// int	t4 = get_us();
// printf("t3 ms [%llu]\n", t3);
// printf("t4 ms [%llu]\n", t4);
// printf("Time diff in { us } [%llu]\n", t4 - t3);
