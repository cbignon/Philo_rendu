/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:52:48 by cbignon           #+#    #+#             */
/*   Updated: 2022/01/18 14:39:34 by cbignon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_struc(t_data *data, int ac, char **av)
{
	int		i;

	i = 0;
	data->args = try_to_malloc(data->args, sizeof(t_arg));
	if (!data->args)
		return (1);
	data->start = get_time();
	if (init_arg(data, ac, av))
		return (1);
	return (0);
}

int	init_arg(t_data *data, int argc, char **argv)
{
	data->args->nb_philo = ft_atoui(argv[1]);
	data->args->t_to_die = ft_atoui(argv[2]);
	data->args->t_to_eat = ft_atoui(argv[3]);
	data->args->t_to_sleep = ft_atoui(argv[4]);
	data->args->nb_meals = -1;
	data->args->on = 1;
	if (argc == 6)
		data->args->nb_meals = ft_atoui(argv[5]);
	if (check_values(data->args))
	{
		free(data);
		return (1);
	}
	data->philo = try_to_malloc(data->philo,
			(sizeof(t_philo) * data->args->nb_philo));
	if (pthread_mutex_init(&data->args->arg_mutex, NULL) || !data->philo
		|| pthread_mutex_init(&data->args->print_mutex, NULL))
		return (print_error("An error occured"));
	if (init_philo(data) || init_forks(data))
		return (1);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	data->forks = try_to_malloc(data->forks,
			(sizeof(t_mut) * data->args->nb_philo));
	if (!data->forks)
	{
		clean_all(data);
		return (1);
	}
	while (++i < data->args->nb_philo)
	{
		data->philo[i].start = data->start;
		data->philo[i].args = data->args;
		data->philo[i].index = i + 1;
		data->philo[i].live = 1;
		data->philo[i].last_meal = 0;
		data->philo[i].meals_count = 0;
		data->philo[i].hungry = 1;
		if (pthread_mutex_init(&data->philo[i].count_mut, NULL))
			return (print_error("An error occured"));
	}
	if (attribute_friends_forks(data))
		return (1);
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i].mut, NULL))
			return (print_error("An error occured"));
		data->philo[i].fork = &data->forks[i];
		data->philo[i].fork->state = FREE;
		i++;
	}
	return (0);
}

int	attribute_friends_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args->nb_philo)
	{
		if (i < data->args->nb_philo - 1)
			data->philo[i].friends_fork = &data->forks[i + 1];
		else
			data->philo[i].friends_fork = &data->forks[0];
		i++;
	}
	return (0);
}
