/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:00:00 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/08 00:00:00 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"
#include "../includes/headers/helpers.h"

bool	mutex_init_err(t_data *data, int i)
{
	int	err;

	while (--i >= 0)
	{
		err = pthread_mutex_destroy(&data->forks[i]);
		if (err != 0)
			return (ft_putnbr_fd(err, 2), false);
	}
	return (true);
}

bool	mutex_init_philos(t_data *data)
{
	int	i;
	int	err;

	i = -1;
	while (++i < data->num_philos)
	{
		err = pthread_mutex_init(&data->forks[i], NULL);
		if (err != 0)
		{
			if (mutex_init_err(data, i) == false)
				return (ft_putendl_fd(" :Mutex destroy error", 2), false);
			return (ft_putnbr_fd(err, 2), false);
		}
		err = pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		if (err != 0)
			return (ft_putnbr_fd(err, 2), false);
	}
	return (true);
}

bool	mutex_init(t_data *data)
{
	int	err;

	if (mutex_init_philos(data) == false)
		return (false);
	err = pthread_mutex_init(&data->start_mutex, NULL);
	if (err != 0)
		return (ft_putnbr_fd(err, 2), false);
	err = pthread_mutex_init(&data->print_mutex, NULL);
	if (err != 0)
		return (ft_putnbr_fd(err, 2), false);
	err = pthread_mutex_init(&data->someone_died_mutex, NULL);
	if (err != 0)
		return (ft_putnbr_fd(err, 2), false);
	err = pthread_mutex_init(&data->ready_mutex, NULL);
	if (err != 0)
		return (ft_putnbr_fd(err, 2), false);
	data->ready_count = 0;
	return (true);
}
