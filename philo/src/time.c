/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:50:19 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/11 11:20:59 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Get time since 1970 in millisecond, using gettimeofday() function.
	time_t		tv_sec;		>> seconds since Jan. 1, 1970
	suseconds_t	tv_usec;	>> and microseconds
*/
int64_t	get_abs_time(void)
{
	struct timeval	t;
	int64_t			s_to_ms; // maybe uint64_t because there is no negative value
	int64_t			u_to_ms;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	s_to_ms = t.tv_sec * 1000;
	u_to_ms = t.tv_usec / 1000;
	return (s_to_ms + u_to_ms);
}

void	accurate_sleep_ms(int64_t time_to_sleep)
{
	int64_t	now;

	now = get_abs_time();
	while (get_abs_time() < now + time_to_sleep) // 400
		usleep(10); // instead of 400000 sleep 50 * (counter - now) // ?????? 10 or 50
}

// void	accurate_sleep_ms(int64_t n)
// {
// 	int64_t	now = get_abs_time();
// 	int64_t	counter = get_abs_time();
// 	while (counter - now < n) // 400
// 	{
// 		usleep(10); // instead of 400000 sleep 10 * (counter - now)
// 		counter = get_abs_time();
// 	}
// }

/*
	Returns the current time, in relation to the beginning of the
	philosopher routines.
*/
int64_t	get_rel_time(int64_t clock_start)
{
	return (get_abs_time() - clock_start);
}
