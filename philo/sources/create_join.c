/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:39:09 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 19:36:46 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"
#include "../includes/headers/helpers.h"

bool	create_threads(t_data *data, pthread_t *threads)
{
	int	err;
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		err = pthread_create(&threads[i], NULL,
				philo_life_start, &data->philos[i]);
		if (err != 0)
			return (ft_putnbr_fd(err, 2),
				ft_putstr_fd(" :Thread create error ", 2), false);
	}
	return (true);
}

bool	join_threads(t_data *data, pthread_t *threads)
{
	int	err;
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		err = pthread_join(threads[i], NULL);
		if (err != 0)
			return (ft_putnbr_fd(err, 2),
				ft_putendl_fd(" :Thread join error", 2), false);
	}
	return (true);
}

bool	create_and_join_threads(t_data *data)
{
	pthread_t	*threads;
	pthread_t	monitor_thread;

	threads = data->threads;
	if (data->num_philos == 1)
	{
		data->start_time = get_time_in_ms();
		if (one_philo(data) == false)
			return (false);
		return (true);
	}
	pthread_mutex_lock(&data->start_mutex);
	if (create_threads(data, threads) == false)
		return (false);
	usleep(data->num_philos * 10000);
	data->start_time = get_time_in_ms();
	pthread_mutex_unlock(&data->start_mutex);
	pthread_create(&monitor_thread, NULL, death_monitor, data);
	join_threads(data, threads);
	pthread_join(monitor_thread, NULL);
	return (true);
}
