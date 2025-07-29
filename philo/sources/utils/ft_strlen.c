/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:57:48 by miyolchy          #+#    #+#             */
/*   Updated: 2025/07/29 17:41:20 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/helpers.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}
