/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:32:19 by cbignon           #+#    #+#             */
/*   Updated: 2022/01/13 14:48:53 by cbignon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosophers(t_data *data)
{
	int		n;

	n = 0;
	pthread_mutex_lock(&data->args->arg_mutex);
	n = data->args->nb_philo;
	pthread_mutex_unlock(&data->args->arg_mutex);
	while (1)
	{
		if (check_death(data->philo, data, n))
			return (1);
	}
	return (0);
}

int	check_death(t_philo *philo, t_data *data, int n)
{
	int		i;

	i = -1;
	while (++i < n)
	{
		pthread_mutex_lock(&philo[i].count_mut);
		if (get_moment(data->start) > philo[i].last_meal + data->args->t_to_die)
		{
			pthread_mutex_unlock(&philo[i].count_mut);
			pthread_mutex_lock(&data->args->arg_mutex);
			data->args->on = 0;
			pthread_mutex_unlock(&data->args->arg_mutex);
			pthread_mutex_lock(&data->args->print_mutex);
			print_death(&philo[i]);
			pthread_mutex_unlock(&data->args->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].count_mut);
	}
	if (data->args->nb_meals > 0)
	{
		if (check_hungry(data->philo, data, n))
			return (1);
	}
	return (0);
}

int	check_hungry(t_philo *philo, t_data *data, int n)
{
	int	i;
	int	full;

	i = 0;
	full = 0;
	while (i < n)
	{
		pthread_mutex_lock(&philo[i].count_mut);
		if (!philo[i].hungry)
			full++;
		pthread_mutex_unlock(&philo[i].count_mut);
		i++;
	}
	if (full == data->args->nb_philo)
	{
		pthread_mutex_lock(&data->args->arg_mutex);
		data->args->on = 0;
		pthread_mutex_unlock(&data->args->arg_mutex);
		return (1);
	}
	return (0);
}
