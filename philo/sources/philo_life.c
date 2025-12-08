/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:21:34 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 20:46:30 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"

bool	philo_alive(t_philo *philo)
{
	bool	died;

	pthread_mutex_lock(&philo->data->someone_died_mutex);
	died = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->someone_died_mutex);
	return (!died);
}

void	philo_life(t_philo *philo)
{
	while (philo_alive(philo))
	{
		if (perform_meal(philo) == false)
			break ;
		if (reached_meal_goal(philo))
			break ;
		philo_print(philo, "is sleeping");
		if (philo_sleep_time_control(philo) == false)
			break ;
		apply_tight_delay(philo);
		apply_odd_delay(philo);
		philo_print(philo, "is thinking");
		if (philo->data->num_philos % 2 == 1)
			usleep(300);
	}
}

void	*philo_life_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->start_mutex);
	pthread_mutex_unlock(&philo->data->start_mutex);
	if (philo->id % 2 == 0)
		usleep(500);
	philo->last_meal_time = philo->data->start_time;
	pthread_mutex_lock(&philo->data->ready_mutex);
	philo->data->ready_count++;
	pthread_mutex_unlock(&philo->data->ready_mutex);
	philo_life(philo);
	return (NULL);
}
