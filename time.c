/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 13:40:34 by cbignon           #+#    #+#             */
/*   Updated: 2022/01/11 13:40:57 by cbignon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;
	long			ret;

	gettimeofday(&time, NULL);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

long	get_moment(long start)
{
	long	now;

	now = get_time();
	return (now - start);
}

void	ft_usleep(long usec)
{
	long	start;

	start = get_time();
	while (get_time() - start < usec)
		usleep(usec / 10);
}
