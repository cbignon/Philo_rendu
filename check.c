/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:16:22 by cbignon           #+#    #+#             */
/*   Updated: 2022/01/11 14:22:05 by cbignon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arg(char **arg, int c)
{
	int	i;
	int	j;

	i = 1;
	while (i < c)
	{
		j = 0;
		while (arg[i][j])
		{
			if (is_digit(arg[i][j]) || arg[i][j] == ' ')
				j++;
			else
				return (1);
		}
		if (check_limits(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_limits(char *arg)
{
	int	len;
	int	u_len;
	int	i;

	len = ft_strlen(arg);
	u_len = ft_strlen(UINT_MAX_STR);
	i = 0;
	if (len < u_len)
		return (0);
	else if (len > u_len)
		return (1);
	while (arg[i])
	{
		if (arg[i] < UINT_MAX_STR[i])
			return (0);
		if (arg[i] > UINT_MAX_STR[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_values(t_arg *arg)
{
	if (arg->nb_philo < 1 || arg->nb_philo > 200)
	{
		clean_args(arg);
		return (print_error("Philo must be between 1 and 200"));
	}
	if (arg->t_to_die < 1 || arg->t_to_eat < 1
		|| arg->t_to_sleep < 1)
	{
		clean_args(arg);
		return (print_error("Please enter numbers between '0' and UINT MAX"));
	}
	if (arg->nb_meals == 0)
	{
		clean_args(arg);
		return (print_error("Please enter a valid number of meals"));
	}
	return (0);
}
