/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_put_forks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:01:07 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 20:04:19 by miyolchy         ###   ########.fr       */
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

void	philo_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
		take_odd_forks(philo);
	else
		take_even_forks(philo);
}

void	philo_put_down_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
		put_down_odd_forks(philo);
	else
		put_down_even_forks(philo);
}
