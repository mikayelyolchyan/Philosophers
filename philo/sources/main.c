/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:43:47 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 19:37:07 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"
#include "../includes/headers/helpers.h"

void	print_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		printf("id = %d\n", data->philos[i].id);
		printf("meals_eaten = %d\n", data->philos[i].meals_eaten);
		printf("last_meal_time = %lld\n", data->philos[i].last_meal_time);
		printf("left_fork = %p\n", data->philos[i].left_fork);
		printf("right_fort = %p\n", data->philos[i].right_fork);
		printf("data = %p\n", data->philos[i].data);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_putendl_fd("Incorrect number of arguments", 2), 1);
	memset(&data, 0, sizeof(t_data));
	if (parse_args(&data, argv) == false)
		return (1);
	if (allocations(&data) == false)
		return (ft_putendl_fd("Allocation error", 2), 1);
	if (initializations(&data) == false)
	{
		ending_free(&data);
		return (1);
	}
	create_and_join_threads(&data);
	if (ending_destroy(&data) == false)
		return (ft_putendl_fd(" :Mutex destroy error", 2),
			ending_free(&data), 1);
	ending_free(&data);
	return (0);
}
