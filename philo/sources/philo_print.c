/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:00:12 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 19:52:48 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"
#include "../includes/headers/helpers.h"

void	philo_print(t_philo *philo, const char *str)
{
	long long		timestamp;
	bool			died;

	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->someone_died_mutex);
	died = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->someone_died_mutex);
	if (died == false || ft_strncmp(str, "died", 4) == 0)
	{
		timestamp = get_time_in_ms() - philo->data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
