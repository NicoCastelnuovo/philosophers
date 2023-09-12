/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 09:05:42 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/12 14:54:12 by ncasteln         ###   ########.fr       */
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

void	print_state(t_philo *philo)
{
	if (!philo)
		return ;
	printf("[%d]\n", philo->id);
	if (philo->turn == 0)
		printf("__PHILO [%c][%s 0]__\n", (philo->id) + 96, "starter");
	else
		printf("__PHILO [%c][%s 1]__\n", (philo->id) + 96, "queued");
	printf("%d %d has taken a fork\n", 0, philo->id);
	printf("%d %d is eating\n", 0, philo->id);
	printf("%d %d is sleeping\n", 0, philo->id);
	printf("%d %d is thinking\n", 0, philo->id);
	printf("%d %d died\n", 0, philo->id);
	printf("forks: [%d] < [%c] > [%d]\n\n", *(philo->fork[0]), (philo->id) + 96, *(philo->fork[1]));
}
