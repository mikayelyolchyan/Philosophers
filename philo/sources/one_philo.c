/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:57:28 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 19:37:38 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"
#include "../includes/headers/helpers.h"

void	*one_philo_life_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal_time = philo->data->start_time;
	while (philo_alive(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		philo_print(philo, "has taken a fork");
		usleep(philo->data->time_to_die * 1000);
		philo_print(philo, "died");
		pthread_mutex_unlock(philo->left_fork);
		break ;
	}
	return (NULL);
}

bool	one_philo(t_data *data)
{
	pthread_t	thread;
	int			err;

	err = pthread_create(&thread, NULL, one_philo_life_start, &data->philos[0]);
	if (err != 0)
		return (ft_putnbr_fd(err, 2), \
			ft_putstr_fd(" :Thread create error ", 2), false);
	err = pthread_join(thread, NULL);
	if (err != 0)
		return (ft_putnbr_fd(err, 2), \
			ft_putendl_fd(" :Thread join error", 2), false);
	return (true);
}
