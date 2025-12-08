/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_put_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 22:50:00 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 22:50:00 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"

void	choose_forks(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	else
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
}

bool	lock_second_fork(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	pthread_mutex_lock(second);
	philo_print(philo, "has taken a fork");
	if (get_someone_died(philo->data))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		waiter_exit(philo);
		return (false);
	}
	return (true);
}
