/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 11:57:42 by cbignon           #+#    #+#             */
/*   Updated: 2022/01/13 15:22:23 by cbignon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*god_ft(void *data)
{
	t_data	*dt;

	dt = (t_data *)data;
	if (dt->args->nb_philo == 1)
		return (NULL);
	while (1)
	{
		if (check_philosophers(dt) == 1)
			break ;
	}
	return (NULL);
}

void	*philo_ft(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->args->nb_philo == 1)
	{
		print_status(ph, "has taken a fork");
		ft_usleep(ph->args->t_to_die + 1);
		print_death(ph);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&ph->args->arg_mutex);
		if (!ph->args->on)
		{
			pthread_mutex_unlock(&ph->args->arg_mutex);
			break ;
		}
		pthread_mutex_unlock(&ph->args->arg_mutex);
		philo_take_forks(ph);
	}
	return (NULL);
}

int	create_thread(t_data *data)
{
	int			i;
	pthread_t	god;

	i = -1;
	pthread_create(&god, NULL, god_ft, (void *)data);
	while (++i < data->args->nb_philo)
	{
		if ((i + 1) % 2)
			pthread_create(&data->philo[i].tid, NULL, philo_ft,
				(void *)&data->philo[i]);
	}
	ft_usleep(data->args->t_to_eat);
	i = -1;
	while (++i < data->args->nb_philo)
	{
		if ((i + 1) % 2 == 0)
			pthread_create(&data->philo[i].tid, NULL, philo_ft,
				(void *)&data->philo[i]);
	}
	pthread_join(god, NULL);
	i = -1;
	while (++i < data->args->nb_philo)
		pthread_join(data->philo[i].tid, NULL);
	return (0);
}
