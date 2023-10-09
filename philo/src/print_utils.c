/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 09:05:42 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/09 08:43:36 by ncasteln         ###   ########.fr       */
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

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (i < ft_strlen(s))
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putnbr_fd(int n, int fd)
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

void	print_single_philo(t_philo *philo)
{

	if (!philo)
		return ;
	printf("__PHILO [%d]__", philo->id + 1);
	printf("n_eat: [%d]\n\n", philo->n_eat);
}

void	print_all_philo(t_philo **philo)
{
	int	i;

	if (!philo)
		return ;
	i = 0;
	while (philo[i])
	{
		print_single_philo(philo[i]);
		i++;
	}
}

void	print_tmstmp(t_philo *philo, t_action what, int64_t when)
{
	int		who;

	who = philo->id + 1;
	pthread_mutex_lock(philo->print_lock);
	if (!philo->time->dead_flag)
	{
		if (what == FORK)
			printf("%llu %d has taken a fork\n", when, who);
		else if (what == EAT)
			printf("%llu %d is eating\n", when, who);
		else if (what == SLEEP)
			printf("%llu %d is sleeping\n", when, who);
		else if (what == THINK)
			printf("%llu %d is thinking\n", when, who);
	}
	pthread_mutex_unlock(philo->print_lock);
}
