/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:21:34 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 19:38:25 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"

bool	philo_alive(t_philo *philo)
{
	bool	died;

	pthread_mutex_lock(&philo->data->someone_died_mutex);
	died = philo->data->someone_died;
	if (died == false && \
		((get_time_in_ms() - philo->last_meal_time) > philo->data->time_to_die))
	{
		philo->data->someone_died = true;
		pthread_mutex_unlock(&philo->data->someone_died_mutex);
		philo_print(philo, "died");
		philo_put_down_fork(philo);
		return (false);
	}
	pthread_mutex_unlock(&philo->data->someone_died_mutex);
	if (died)
	{
		philo_put_down_fork(philo);
		return (false);
	}
	return (true);
}

void	philo_life(t_philo *philo)
{
	while (philo_alive(philo))
	{
		philo_take_fork(philo);
		philo->last_meal_time = get_time_in_ms();
		philo_print(philo, "is eating");
		if (philo_eat_time_control(philo) == false)
			break ;
		philo_put_down_fork(philo);
		philo->meals_eaten++;
		if (philo->meals_eaten == philo->data->must_eat)
			break ;
		philo_print(philo, "is sleeping");
		if (philo_sleep_time_control(philo) == false)
			break ;
		philo_print(philo, "is thinking");
	}
}

void	*philo_life_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->start_mutex);
	pthread_mutex_unlock(&philo->data->start_mutex);
	philo->last_meal_time = philo->data->start_time;
	philo_life(philo);
	return (NULL);
}
