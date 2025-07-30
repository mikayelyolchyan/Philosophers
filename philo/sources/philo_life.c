/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:21:34 by miyolchy          #+#    #+#             */
/*   Updated: 2025/07/31 00:38:44 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"

unsigned long long	get_time_in_ms(void)
{
    struct timeval	tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philo_print(t_philo *philo, const char *str)
{
	long timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_time_in_ms() - philo->data->start_time;
	printf("%ld Philo %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

bool	philo_alive(t_philo *philo)
{
	if ((get_time_in_ms() - philo->last_meal_time) > philo->data->time_to_die)
	{
		philo->data->someone_died = true;
		philo_print(philo, " is die");
		return (false);
	}
	if (philo->data->someone_died == true)
		return (false);
	return (true);
}

void	philo_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		philo_print(philo, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
		philo_print(philo, "has taken right fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo_print(philo, "has taken right fork");
		pthread_mutex_lock(philo->left_fork);
		philo_print(philo, "has taken left fork");
	}
}


void	philo_put_down_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo_print(philo, "put down left fork");
		pthread_mutex_unlock(philo->right_fork);
		philo_print(philo, "put down right fork");
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		philo_print(philo, "put down right fork");
		pthread_mutex_unlock(philo->left_fork);
		philo_print(philo, "put down left fork");
	}
}

bool	philo_eat_time_control(t_philo *philo)
{
    long	start_eat;

    start_eat = get_time_in_ms();
    while (get_time_in_ms() - start_eat < philo->data->time_to_eat)
    {
        if (philo_alive(philo) == false)
            return (false);
        //usleep(500); // маленькая пауза, чтобы не грузить процессор
    }
	return (true);
}

bool	philo_sleep_time_control(t_philo *philo)
{
    long	start_sleep;

    start_sleep = get_time_in_ms();
    while (get_time_in_ms() - start_sleep < philo->data->time_to_sleep)
    {
        if (philo_alive(philo) == false)
            return (false);
        //usleep(500); // маленькая пауза, чтобы не грузить процессор
    }
	return (true);
}

void	philo_life(t_philo *philo)
{
	while (philo_alive(philo))
	{
		philo_take_fork(philo);
		philo->last_meal_time = get_time_in_ms();
		philo_print(philo, " is eating");
		if (philo_eat_time_control(philo) == false)
			break ;
		philo_put_down_fork(philo);
		philo_print(philo, " is sleeping");
		if (philo_sleep_time_control(philo) == false)
			break ;
		philo_print(philo, " is thinking");
		//usleep(500);
	}
}

void	*philo_life_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Philo %d wait\n", philo->id);
	pthread_mutex_lock(&philo->data->start_mutex);
	pthread_mutex_unlock(&philo->data->start_mutex);
	printf("Philo %d start\n", philo->id);
	philo->last_meal_time = philo->data->start_time;
	philo_life(philo);
	return (NULL);
}
