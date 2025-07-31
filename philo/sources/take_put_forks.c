/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_put_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:01:07 by miyolchy          #+#    #+#             */
/*   Updated: 2025/07/31 18:44:40 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"

void	philo_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		philo->left_fork_taken = true;
		philo_print(philo, "has taken a fork");
		if (philo->data->someone_died == true)
		{
			pthread_mutex_unlock(philo->left_fork);
			philo->left_fork_taken = false;
		}
		pthread_mutex_lock(philo->right_fork);
		philo->right_fork_taken = true;
		philo_print(philo, "has taken a fork");
		if (philo->data->someone_died == true)
		{
			pthread_mutex_unlock(philo->left_fork);
			philo->left_fork_taken = false;
			pthread_mutex_unlock(philo->right_fork);
			philo->right_fork_taken = false;
		}
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo->right_fork_taken = true;
		philo_print(philo, "has taken a fork");
		if (philo->data->someone_died == true)
		{
			pthread_mutex_unlock(philo->right_fork);
			philo->right_fork_taken = false;
		}
		pthread_mutex_lock(philo->left_fork);
		philo->left_fork_taken = true;
		if (philo->data->someone_died == true)
		{
			pthread_mutex_unlock(philo->left_fork);
			philo->left_fork_taken = false;
			pthread_mutex_unlock(philo->right_fork);
			philo->right_fork_taken = false;
		}
		philo_print(philo, "has taken a fork");
	}
}

void	philo_put_down_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
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
	else
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
}
