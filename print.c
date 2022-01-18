/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:21:31 by cbignon           #+#    #+#             */
/*   Updated: 2022/01/18 11:28:13 by cbignon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_status(t_philo *philo, char *status)
{
	long	time;

	time = get_moment(philo->start);
	pthread_mutex_lock(&philo->args->arg_mutex);
	if (philo->args->on == 0)
	{
		pthread_mutex_unlock(&philo->args->arg_mutex);
		return (1);
	}
	printf("%ld %d %s\n", time, philo->index, status);
	pthread_mutex_unlock(&philo->args->arg_mutex);
	return (0);
}

void	print_death(t_philo *philo)
{
	long	time;

	time = get_moment(philo->start);
	printf("%ld %d died\n", time, philo->index);
}

int	print_error(char *message)
{
	printf("%s\n", message);
	return (1);
}
