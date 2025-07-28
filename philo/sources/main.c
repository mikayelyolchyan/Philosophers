/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:43:47 by miyolchy          #+#    #+#             */
/*   Updated: 2025/07/28 21:05:05 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"
#include "../includes/headers/helpers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (write(2, "Incorrect number of arguments\n", 30), 1);
	data.num_philos = ft_atoi(argv[1]);
	if (allocation(&data) == false)
		return (write(2, "Allocation error\n", 17), 1);
	
	free(data.forks);
	free(data.philos);
	return (0);
}
