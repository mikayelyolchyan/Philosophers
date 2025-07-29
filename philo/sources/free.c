/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:46:14 by miyolchy          #+#    #+#             */
/*   Updated: 2025/07/29 18:51:42 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers/philo.h"

void	ending_free(t_data *data)
{
	free(data->philos);
	free(data->forks);
	free(data->threads);
}
