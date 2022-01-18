/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 12:20:02 by cbignon           #+#    #+#             */
/*   Updated: 2022/01/18 14:15:24 by cbignon          ###   ########.fr       */
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
			else
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
	philo->meals_count++;
	if (philo->meals_count == philo->args->nb_meals)
		philo->hungry = 0;
	pthread_mutex_unlock(&philo->count_mut);
	ft_usleep(philo->args->t_to_eat);
	change_fork_state(philo->friends_fork, LOCK, FREE);
	change_fork_state(philo->fork, LOCK, FREE);
	return (philo_sleep(philo));
}

int	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	print_status(philo, "is sleeping");
	pthread_mutex_unlock(&philo->args->print_mutex);
	ft_usleep(philo->args->t_to_sleep);
	return (philo_think(philo));
}

int	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print_mutex);
	print_status(philo, "is thinking");
	pthread_mutex_unlock(&philo->args->print_mutex);
	if (philo->args->nb_philo % 2)
		usleep(10);
	return (0);
}
