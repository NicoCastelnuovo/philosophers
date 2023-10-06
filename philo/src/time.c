/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:50:19 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/06 12:08:52 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Get time since 1970 in millisecond, using gettimeofday() function.
	time_t		tv_sec;		>> seconds since Jan. 1, 1970
	suseconds_t	tv_usec;	>> and microseconds
*/
int64_t	get_time_ms(void)
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

int64_t	get_time_us(void)
{
	struct timeval	t;
	int64_t			s_to_us;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	s_to_us = t.tv_sec * 1000000;
	return (s_to_us + t.tv_usec);
}

void	accurate_sleep_ms(int64_t n)
{
	int64_t	now = get_time_ms();
	int64_t	counter = get_time_ms();
	while (counter - now < n) // 400
	{
		usleep(10); // instead of 400000 sleep 10 * (counter - now)
		counter = get_time_ms();
	}
}

void	accurate_sleep_us(int64_t time)
{
	int64_t	now = get_time_us();
	int64_t	counter = get_time_us();
	while (counter - now < time) // 400
	{
		usleep(10); // instead of 400000 sleep 10 * (counter - now)
		// dead_check ???
		counter = get_time_us();
	}
}

/*
	This function returns the current time, in relation to the beginning
	of the philosopher routines.
*/
int64_t	now_ms(int64_t clock_start)
{
	return (get_time_ms() - clock_start);
}

int64_t	now_us(int64_t clock_start)
{
	return (get_time_us() - clock_start);
}

// #include "philo.h"

// /*
// 	Get time since 1970 in millisecond, using gettimeofday() function.
// 	time_t		tv_sec;		>> seconds since Jan. 1, 1970
// 	suseconds_t	tv_usec;	>> and microseconds
// */
// int64_t	get_time_ms(void)
// {
// 	struct timeval	t;
// 	int64_t			s_to_ms; // maybe uint64_t because there is no negative value
// 	int64_t			u_to_ms;

// 	if (gettimeofday(&t, NULL) == -1)
// 		return (0);
// 	s_to_ms = t.tv_sec * 1000;
// 	u_to_ms = t.tv_usec / 1000;
// 	return (s_to_ms + u_to_ms);
// }

// int64_t	get_time_us(void)
// {
// 	struct timeval	t;
// 	int64_t			s_to_us;

// 	if (gettimeofday(&t, NULL) == -1)
// 		return (0);
// 	s_to_us = t.tv_sec * 1000000;
// 	return (s_to_us + t.tv_usec);
// }

// void	accurate_sleep_ms(int64_t n)
// {
// 	int64_t	now = get_time_ms();
// 	int64_t	counter = get_time_ms();
// 	while (counter - now < n) // 400
// 	{
// 		usleep(10); // instead of 400000 sleep 10 * (counter - now)
// 		counter = get_time_ms();
// 	}
// }

// void	accurate_sleep_us(int64_t n)
// {
// 	int64_t	now = get_time_us();
// 	int64_t	counter = get_time_us();
// 	while (counter - now < n) // 400
// 	{
// 		usleep(10); // instead of 400000 sleep 10 * (counter - now)
// 		// check if someone dead here ???
// 		counter = get_time_us();
// 	}
// }

// /*
// 	This function returns the current time, in relation to the beginning
// 	of the philosopher routines.
// */
// int64_t	now_ms(int64_t clock_start)
// {
// 	return (get_time_ms() - clock_start);
// }

// int64_t	now_us(int64_t clock_start)
// {
// 	return (get_time_us() - clock_start);
// }
