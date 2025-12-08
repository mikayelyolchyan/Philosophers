/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:00:00 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/08 12:00:00 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"

void	finish_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

bool	reached_meal_goal(t_philo *philo)
{
	if (philo->data->must_eat == -1)
		return (false);
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->meals_eaten >= philo->data->must_eat)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (false);
}

void	apply_tight_delay(t_philo *philo)
{
	long	slack;

	slack = philo->data->time_to_die - (philo->data->time_to_eat
			+ philo->data->time_to_sleep);
	if (slack < (long)philo->data->time_to_sleep
		&& (philo->data->num_philos % 2 == 1
			|| philo->data->time_to_sleep < philo->data->time_to_eat))
		usleep(((philo->data->time_to_sleep + philo->data->time_to_eat) * 1000)
			+ 1000);
}

void	apply_odd_delay(t_philo *philo)
{
	if (philo->data->num_philos % 2 == 1
		&& philo->data->time_to_eat > philo->data->time_to_sleep)
		usleep((philo->data->time_to_eat - philo->data->time_to_sleep) * 1000);
}

bool	perform_meal(t_philo *philo)
{
	if (philo_take_fork(philo) == false)
		return (false);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	philo_print(philo, "is eating");
	if (philo_eat_time_control(philo) == false)
	{
		philo_put_down_fork(philo);
		return (false);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	philo_put_down_fork(philo);
	finish_meal(philo);
	return (true);
}
