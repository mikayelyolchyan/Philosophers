/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 00:00:00 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/08 00:00:00 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"

bool	try_lock_second_fork(pthread_mutex_t *fork, t_philo *philo)
{
	while (pthread_mutex_trylock(fork) != 0)
	{
		if (get_someone_died(philo->data))
			return (false);
		usleep(10);
	}
	return (true);
}

void	release_forks_on_death(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	philo->left_fork_taken = false;
	pthread_mutex_unlock(philo->right_fork);
	philo->right_fork_taken = false;
}
