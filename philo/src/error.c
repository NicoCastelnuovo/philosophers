/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:08:19 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/11 16:04:25 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(int err_code, char *file, int line)
{
	ft_putstr_fd("Error: ", 2);
	if (err_code == EARGC)
		ft_putstr_fd("invalid argument", 2);
	if (err_code == EMALLOC)
		ft_putstr_fd("malloc() ", 2);
	if (err_code == ECREATE_THREAD)
		ft_putstr_fd("pthread_create()", 2);
	if (err_code == ETHJOIN)
		ft_putstr_fd("pthread_join()", 2);
	if (err_code == EMUTEX)
		ft_putstr_fd("pthread_mutex_init()", 2);
	if (err_code == ECREATE_PHILO)
		ft_putstr_fd("create_philosophers()", 2);
	ft_putstr_fd(" in ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" @ line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putchar_fd('\n', 2);
	return (err_code);
}
