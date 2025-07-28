/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:43:47 by miyolchy          #+#    #+#             */
/*   Updated: 2025/07/28 21:12:52 by miyolchy         ###   ########.fr       */
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
	initialization(&data);
	free(data.forks);
	free(data.philos);
	return (0);
}
void	print_data(t_data *data)
{
	int i = 0;

	while (i < data->num_philos)
	{
		printf("id = %d\n", data->philos[i].id);
		printf("meals_eaten = %d\n", data->philos[i].meals_eaten);
		printf("last_meal_time = %d\n", data->philos[i].last_meal_time);
		printf("left_fork = %p\n", data->philos[i].left_fork);
		printf("right_fort = %p\n", data->philos[i].right_fork);
		printf("data = %p\n", data->philos[i].data);
		i++;
	}
}
