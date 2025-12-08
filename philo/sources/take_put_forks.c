/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_put_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:01:07 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 22:25:58 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"

bool	get_someone_died(t_data *data)
{
	bool	val;

	pthread_mutex_lock(&data->someone_died_mutex);
	val = data->someone_died;
	pthread_mutex_unlock(&data->someone_died_mutex);
	return (val);
}

void	waiter_exit(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->waiter_mutex);
	philo->data->eating_count--;
	pthread_mutex_unlock(&philo->data->waiter_mutex);
}

static bool	waiter_enter(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->waiter_mutex);
	if (get_someone_died(philo->data))
	{
		pthread_mutex_unlock(&philo->data->waiter_mutex);
		return (false);
	}
	philo->data->eating_count++;
	pthread_mutex_unlock(&philo->data->waiter_mutex);
	return (true);
}

bool	philo_take_fork(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (waiter_enter(philo) == false)
		return (false);
	if (philo->data->num_philos % 2 == 1
		&& philo->id == philo->data->num_philos)
		usleep(150);
	choose_forks(philo, &first, &second);
	pthread_mutex_lock(first);
	philo_print(philo, "has taken a fork");
	if (get_someone_died(philo->data))
	{
		pthread_mutex_unlock(first);
		waiter_exit(philo);
		return (false);
	}
	return (lock_second_fork(philo, first, second));
}

void	philo_put_down_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	waiter_exit(philo);
}
