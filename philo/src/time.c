/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:50:19 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/12 12:21:20 by ncasteln         ###   ########.fr       */
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
	int64_t			s_to_ms;
	int64_t			u_to_ms;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	s_to_ms = t.tv_sec * 1000;
	u_to_ms = t.tv_usec / 1000;
	return (s_to_ms + u_to_ms);
}

/*
	The philo has to sleep for action_time (example 200). To do that, instead
	of doing usleep(200000), it is done in smaller pieces. In every iteration
	it get_rel_time() so that the interval_end is not overtaken.
*/
void	accurate_sleep_ms(int64_t action_time, int64_t clock_start)
{
	int64_t	interval_start;
	int64_t	interval_end;

	interval_start = get_rel_time(clock_start);
	interval_end = interval_start + action_time;
	while (get_rel_time(clock_start) < interval_end)
		usleep(450);
}

/*
	Returns the current time, in relation to the beginning of the
	philosopher routines.
*/
int64_t	get_rel_time(int64_t clock_start)
{
	return (get_abs_time() - clock_start);
}
