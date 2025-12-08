/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:00:00 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 20:04:19 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"

bool	take_odd_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo->left_fork_taken = true;
	philo_print(philo, "has taken a fork");
	if (get_someone_died(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->left_fork_taken = false;
		return (false);
	}
	if (try_lock_second_fork(philo->right_fork, philo) == false)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->left_fork_taken = false;
		return (false);
	}
	philo->right_fork_taken = true;
	philo_print(philo, "has taken a fork");
	if (get_someone_died(philo->data))
	{
		release_forks_on_death(philo);
		return (false);
	}
	return (true);
}

bool	take_even_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	philo->right_fork_taken = true;
	philo_print(philo, "has taken a fork");
	if (get_someone_died(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		philo->right_fork_taken = false;
		return (false);
	}
	if (try_lock_second_fork(philo->left_fork, philo) == false)
	{
		pthread_mutex_unlock(philo->right_fork);
		philo->right_fork_taken = false;
		return (false);
	}
	philo->left_fork_taken = true;
	philo_print(philo, "has taken a fork");
	if (get_someone_died(philo->data))
	{
		release_forks_on_death(philo);
		return (false);
	}
	return (true);
}

void	put_down_odd_forks(t_philo *philo)
{
	if (philo->left_fork_taken == true)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->left_fork_taken = false;
	}
	if (philo->right_fork_taken == true)
	{
		pthread_mutex_unlock(philo->right_fork);
		philo->right_fork_taken = false;
	}
}

void	put_down_even_forks(t_philo *philo)
{
	if (philo->right_fork_taken == true)
	{
		pthread_mutex_unlock(philo->right_fork);
		philo->right_fork_taken = false;
	}
	if (philo->left_fork_taken == true)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->left_fork_taken = false;
	}
}
