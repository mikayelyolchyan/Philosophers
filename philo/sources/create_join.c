/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:39:09 by miyolchy          #+#    #+#             */
/*   Updated: 2025/07/29 18:56:46 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"
#include "../includes/headers/helpers.h"

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->start_mutex);
	pthread_mutex_unlock(&philo->data->start_mutex);
	printf("Philo %d \n", philo->id);
	return (NULL);
}

bool	create_and_join_threads(t_data *data)
{
	pthread_t	*tds;
	int			err;
	int			i;

	tds = data->threads;
	pthread_mutex_lock(&data->start_mutex);
	i = -1;
	while (++i < data->num_philos)
	{
		err = pthread_create(&tds[i], NULL, philo_routine, &data->philos[i]);
		if (err != 0)
			return (ft_putnbr_fd(err, 2), \
					ft_putstr_fd(" :Thread create error ", 2), false);
	}
	usleep(3000000);
	pthread_mutex_unlock(&data->start_mutex);
	i = -1;
	while (++i < data->num_philos)
	{
		err = pthread_join(tds[i], NULL);
		if (err != 0)
			return (ft_putnbr_fd(err, 2), \
					ft_putendl_fd(" :Thread join error", 2), false);
	}
	return (true);
}
