/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyolchy <miyolchy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:00:41 by miyolchy          #+#    #+#             */
/*   Updated: 2025/07/29 17:01:06 by miyolchy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/helpers.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (fd > 0)
		write(fd, s, ft_strlen(s));
}
