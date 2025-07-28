/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:43:47 by miyolchy          #+#    #+#             */
/*   Updated: 2025/07/28 19:36:19 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"
#include "../includes/headers/helpers.h"

bool	allocation(t_data *data, const int philos_count)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * philos_count);
	if (!data->philos)
		return (false);
	data->forsk = malloc(sizeof(pthread_mutex_t) * philos_count);
	if (!data->forsk)
	{
		free(data->philos);
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		philos_count;

	if (argc != 5 && argc != 6)
		return (write(2, "Incorrect number of arguments\n", 30), 1);
	philos_count = ft_atoi(argv[1]);
	if (allocation(&data, philos_count) == false)
		return (write(2, "Allocation error\n", 17), 1);
	return (0);
}