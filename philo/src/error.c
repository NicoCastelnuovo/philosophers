/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:08:19 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/11 10:37:09 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

static void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = n * -1;
		}
		if (n >= 10)
		{
			ft_putnbr_fd(n / 10, fd);
			n = n % 10;
		}
		if (n < 10)
			ft_putchar_fd(n + 48, fd);
	}
}

static void	print_err(int err_code)
{
	if (err_code == EARG)
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
		ft_putstr_fd("pthread_mutex_destroy()", 2);
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
	ft_putstr_fd(" @line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putchar_fd('\n', 2);
	return (err_code);
}
