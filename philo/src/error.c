/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:08:19 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/04 17:03:19 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_err(int err_code)
{
	if (err_code == EARGC)
		ft_putstr_fd("invalid argument", 2);
	if (err_code == EMALLOC)
		ft_putstr_fd("malloc() ", 2);
	if (err_code == ECREATE_THREAD)
		ft_putstr_fd("pthread_create()", 2);
	if (err_code == ETHJOIN)
		ft_putstr_fd("pthread_join()", 2);
	if (err_code == EMUTEX_INIT)
		ft_putstr_fd("pthread_mutex_init()", 2);
	if (err_code == EMUTEX_DESTROY)
		ft_putstr_fd("pthread_mutex_destroy()", 2); // check errors !!!!
	if (err_code == EGET_TIME)
		ft_putstr_fd("get time failed", 2);
	if (err_code == ECREATE_PHILO)
		ft_putstr_fd("fail creating philo", 2);
}

int	error(int *err_store, int err_code, char *file, int line)
{
	*err_store = err_code;
	ft_putstr_fd("Error: ", 2);
	print_err(err_code);
	ft_putstr_fd(" in ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" @ line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putchar_fd('\n', 2);
	return (err_code);
}
