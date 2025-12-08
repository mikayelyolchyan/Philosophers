/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:57:39 by miyolchy          #+#    #+#             */
/*   Updated: 2025/07/31 20:18:03 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"
#include "../includes/headers/helpers.h"

bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	is_valid(char **argv)
{
	long		l;
	size_t		i;
	size_t		args;

	args = 1;
	while (argv[args])
	{
		i = 0;
		while (i < ft_strlen(argv[args]))
		{
			if (ft_isdigit(argv[args][i]) == false)
				return (false);
			i++;
		}
		if (ft_strlen(argv[args]) > 10)
			return (false);
		l = ft_atoll(argv[args]);
		if (l > INT_MAX || l < 0)
			return (false);
		args++;
	}
	return (true);
}

bool	parse_args(t_data *data, char **argv)
{
	if (is_valid(argv) == true)
	{
		data->num_philos = ft_atoll(argv[1]);
		data->time_to_die = ft_atoll(argv[2]);
		data->time_to_eat = ft_atoll(argv[3]);
		data->time_to_sleep = ft_atoll(argv[4]);
		if (argv[5] != NULL)
			data->must_eat = ft_atoll(argv[5]);
	}
	else
		return (ft_putendl_fd("Incorrect arguments", 2), false);
	if (argv[5] == NULL)
		data->must_eat = -1;
	data->someone_died = false;
	return (true);
}
