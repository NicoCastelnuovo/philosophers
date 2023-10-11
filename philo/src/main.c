/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:57:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/11 13:37:40 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_monastery	data;

	if (create_monastery(&data, argc, argv))
		return (data.err_code);

	if (create_threads(&data))
		return (data.err_code);

	if (join_threads(&data))
		return (data.err_code);

	if (destroy_mutex(&data))
		return (data.err_code);

	free_mem(&data);
	return (0);
}
