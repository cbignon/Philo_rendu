/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:43:31 by cbignon           #+#    #+#             */
/*   Updated: 2022/01/13 14:02:49 by cbignon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_args(t_arg *arg)
{
	if (arg)
	{
		free(arg);
		arg = NULL;
	}
	return (0);
}

int	clean_philo(t_philo *philo)
{
	if (philo)
	{
		free(philo);
		philo = NULL;
	}
	return (0);
}

int	clean_forks(t_mut *forks)
{
	if (forks)
	{
		free(forks);
		forks = NULL;
	}
	return (0);
}

int	clean_all(t_data *data)
{
	if (data->args)
		clean_args(data->args);
	if (data->philo)
		clean_philo(data->philo);
	if (data->forks)
		clean_forks(data->forks);
	if (data)
		free(data);
	data = NULL;
	return (0);
}
