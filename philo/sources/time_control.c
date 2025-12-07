/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:02:10 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 20:36:11 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"

bool	philo_eat_time_control(t_philo *philo)
{
	long	start_eat;

	start_eat = get_time_in_ms();
	while (get_time_in_ms() - start_eat < philo->data->time_to_eat)
	{
		if (philo_alive(philo) == false)
			return (false);
		usleep(100);
	}
	return (true);
}

bool	philo_sleep_time_control(t_philo *philo)
{
	long	start_sleep;

	start_sleep = get_time_in_ms();
	while (get_time_in_ms() - start_sleep < philo->data->time_to_sleep)
	{
		if (philo_alive(philo) == false)
			return (false);
		usleep(100);
	}
	return (true);
}
