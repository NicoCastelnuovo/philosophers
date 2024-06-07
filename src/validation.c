/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:49:03 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/12 12:54:34 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	is_valid_string_format(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '+')
			i++;
		while (ft_isdigit(s[i]))
			i++;
		while (s[i] == ' ')
			i++;
		if (ft_strlen(s) == i)
			return (1);
		return (0);
	}
	return (0);
}

static int	is_valid_integer(char *argv)
{
	long	n;

	if (ft_atol(argv) == 0)
		return (0);
	if (!is_valid_string_format(argv))
		return (0);
	n = ft_atol(argv);
	if (n != (int) n)
		return (0);
	return (1);
}

int	is_valid_input(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_integer(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
