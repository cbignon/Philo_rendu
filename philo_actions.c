/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 12:20:02 by cbignon           #+#    #+#             */
/*   Updated: 2022/01/13 15:26:35 by cbignon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_take_forks(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->args->arg_mutex);
		if (!philo->args->on)
		{
			pthread_mutex_unlock(&philo->args->arg_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->args->arg_mutex);
		if (change_fork_state(philo->fork, FREE, LOCK))
		{
			if (change_fork_state(philo->friends_fork, FREE, LOCK))
				philo_eat(philo);
			change_fork_state(philo->fork, LOCK, FREE);
		}
	}
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	print_status(philo, "has taken a fork");
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_unlock(&philo->args->print_mutex);
	pthread_mutex_lock(&philo->count_mut);
	philo->last_meal = get_moment(philo->start);
	pthread_mutex_unlock(&philo->count_mut);
	ft_usleep(philo->args->t_to_eat);
	change_fork_state(philo->friends_fork, LOCK, FREE);
	change_fork_state(philo->fork, LOCK, FREE);
	pthread_mutex_lock(&philo->args->arg_mutex);
	if (philo->args->nb_meals)
		count_meal(philo);
	pthread_mutex_unlock((&philo->args->arg_mutex));
	return (sleep_or_die(philo));
}

int	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	print_status(philo, "is sleeping");
	pthread_mutex_unlock(&philo->args->print_mutex);
	ft_usleep(philo->args->t_to_sleep);
	pthread_mutex_lock(&philo->args->arg_mutex);
	if (philo->args->on)
	{
		pthread_mutex_unlock(&philo->args->arg_mutex);
		return (philo_think(philo));
	}
	else
	{
		pthread_mutex_unlock(&philo->args->arg_mutex);
		return (1);
	}
}

int	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	if (print_status(philo, "is thinking"))
	{
		pthread_mutex_unlock(&philo->args->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->print_mutex);
	return (0);
}

int	sleep_or_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->arg_mutex);
	if (philo->args->on)
	{
		pthread_mutex_unlock(&philo->args->arg_mutex);
		philo_sleep(philo);
	}
	else
	{
		pthread_mutex_unlock(&philo->args->arg_mutex);
		return (1);
	}
	return (0);
}
