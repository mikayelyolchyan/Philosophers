/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:58:35 by miyolchy          #+#    #+#             */
/*   Updated: 2025/07/31 21:16:00 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"
#include "../includes/headers/helpers.h"

bool	ending_destroy(t_data *data)
{
	int	i;
	int	err;

	i = -1;
	while (++i < data->num_philos)
	{
		err = pthread_mutex_destroy(&data->forks[i]);
		if (err != 0)
			return (printf("fork %d ", i), ft_putnbr_fd(err, 2), false);
	}
	err = pthread_mutex_destroy(&data->start_mutex);
	if (err != 0)
		return (ft_putnbr_fd(err, 2), false);
	err = pthread_mutex_destroy(&data->print_mutex);
	if (err != 0)
		return (ft_putnbr_fd(err, 2), false);
	err = pthread_mutex_destroy(&data->someone_died_mutex);
	if (err != 0)
		return (ft_putnbr_fd(err, 2), false);
	return (true);
}
