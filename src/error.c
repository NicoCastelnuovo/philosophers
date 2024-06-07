/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:08:19 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/11 14:37:11 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

static void	print_err(int err_code)
{
	if (err_code == EARG)
		ft_putstr_fd("invalid argument\n", 2);
	if (err_code == EMALLOC)
		ft_putstr_fd("malloc() \n", 2);
	if (err_code == ECREATE_THREAD)
		ft_putstr_fd("pthread_create()\n", 2);
	if (err_code == ETHJOIN)
		ft_putstr_fd("pthread_join()\n", 2);
	if (err_code == EMUTEX_INIT)
		ft_putstr_fd("pthread_mutex_init()\n", 2);
	if (err_code == EMUTEX_DESTROY)
		ft_putstr_fd("pthread_mutex_destroy()\n", 2);
	if (err_code == EGET_TIME)
		ft_putstr_fd("get time failed\n", 2);
	if (err_code == ECREATE_PHILO)
		ft_putstr_fd("fail creating philo\n", 2);
}

int	error(int *err_store, int err_code)
{
	*err_store = err_code;
	ft_putstr_fd("Error: ", 2);
	print_err(err_code);
	return (err_code);
}
