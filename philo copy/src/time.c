/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:50:19 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/11 11:54:20 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
