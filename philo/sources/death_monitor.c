/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 23:00:00 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 23:00:00 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"

static bool	check_philo_death(t_philo *philo)
{
	unsigned long long	time_diff;

	pthread_mutex_lock(&philo->data->someone_died_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->someone_died_mutex);
		return (true);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->data->must_eat != -1 && philo->meals_eaten >= philo->data->must_eat)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_unlock(&philo->data->someone_died_mutex);
		return (false);
	}
	time_diff = get_time_in_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_diff > philo->data->time_to_die)
	{
		philo->data->someone_died = true;
		pthread_mutex_unlock(&philo->data->someone_died_mutex);
		philo_print(philo, "died");
		return (true);
	}
	pthread_mutex_unlock(&philo->data->someone_died_mutex);
	return (false);
}

static bool	check_meals_done(t_data *data)
{
	int	i;
	int	finished;

	if (data->must_eat == -1)
		return (false);
	finished = 0;
	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals_eaten >= data->must_eat)
			finished++;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
	}
	if (finished == data->num_philos)
	{
		pthread_mutex_lock(&data->someone_died_mutex);
		data->someone_died = true;
		pthread_mutex_unlock(&data->someone_died_mutex);
		return (true);
	}
	return (false);
}

void	*death_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->ready_mutex);
		if (data->ready_count == data->num_philos)
		{
			pthread_mutex_unlock(&data->ready_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->ready_mutex);
		usleep(100);
	}
	while (1)
	{
		i = -1;
		while (++i < data->num_philos)
		{
			if (check_philo_death(&data->philos[i]))
				return (NULL);
		}
		if (check_meals_done(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
