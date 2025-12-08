/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:02:30 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 19:36:22 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"
#include "../includes/headers/helpers.h"

bool	allocations(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (!data->philos || !data->forks || !data->threads)
	{
		ending_free(data);
		return (false);
	}
	return (true);
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].left_fork_taken = false;
		data->philos[i].right_fork_taken = false;
		data->philos[i].data = data;
	}
}

bool	initializations(t_data *data)
{
	if (mutex_init(data) == false)
		return (ft_putendl_fd(" :Mutex init error", 2), false);
	init_philos(data);
	return (true);
}
