/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:04:33 by cbignon           #+#    #+#             */
/*   Updated: 2022/01/13 14:46:55 by cbignon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->args->arg_mutex);
	change_fork_state(philo->friends_fork, LOCK, FREE);
	change_fork_state(philo->fork, LOCK, FREE);
	return (1);
}

int	drop_my_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->args->arg_mutex);
	change_fork_state(philo->fork, LOCK, FREE);
	return (1);
}

int	count_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->count_mut);
	philo->meals_count++;
	if (philo->meals_count == philo->args->nb_meals)
		philo->hungry = 0;
	pthread_mutex_unlock(&philo->count_mut);
	return (0);
}

int	change_fork_state(t_mut *fork, int before, int after)
{
	int	done;

	done = 0;
	pthread_mutex_lock(&fork->mut);
	if (fork->state == before)
	{
		fork->state = after;
		done = 1;
	}
	else
		done = 0;
	pthread_mutex_unlock(&fork->mut);
	return (done);
}
