/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:43:50 by miyolchy          #+#    #+#             */
/*   Updated: 2025/12/07 20:04:19 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
	int						id;
	int						meals_eaten;
	unsigned long long		last_meal_time;
	bool					left_fork_taken;
	bool					right_fork_taken;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	struct s_data			*data;
}	t_philo;

typedef struct s_data
{
	int						num_philos;
	int						must_eat;
	unsigned long long		time_to_die;
	unsigned long long		time_to_eat;
	unsigned long long		time_to_sleep;
	unsigned long long		start_time;
	bool					someone_died;
	pthread_mutex_t			someone_died_mutex;
	pthread_t				*threads;
	pthread_mutex_t			start_mutex;
	pthread_mutex_t			*forks;
	pthread_mutex_t			print_mutex;
	t_philo					*philos;
}	t_data;

bool				allocations(t_data *data);
bool				initializations(t_data *data);
void				ending_free(t_data *data);
bool				create_and_join_threads(t_data *data);
void				*philo_life_start(void *arg);
unsigned long long	get_time_in_ms(void);
bool				one_philo(t_data *data);
bool				philo_eat_time_control(t_philo *philo);
bool				philo_alive(t_philo *philo);
void				philo_print(t_philo *philo, const char *str);
bool				parse_args(t_data *data, char **argv);
bool				ending_destroy(t_data *data);
void				philo_take_fork(t_philo *philo);
void				philo_put_down_fork(t_philo *philo);
bool				get_someone_died(t_data *data);
bool				take_odd_forks(t_philo *philo);
bool				take_even_forks(t_philo *philo);
void				put_down_odd_forks(t_philo *philo);
void				put_down_even_forks(t_philo *philo);
bool				philo_sleep_time_control(t_philo *philo);

#endif
