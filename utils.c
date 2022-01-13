/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:27:38 by cbignon           #+#    #+#             */
/*   Updated: 2022/01/11 14:23:16 by cbignon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoui(char *arg)
{
	unsigned int	n;
	int				i;

	n = 0;
	i = 0;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == 32)
		i++;
	while (is_digit(arg[i]))
	{
		n = n * 10 + (arg[i] - '0');
		i++;
	}
	return (n);
}

void	*try_to_malloc(void *src, int size)
{
	void	*dest;

	dest = malloc(sizeof(char) * size);
	if (dest == NULL)
	{
		printf("A malloc error occured\n");
		return ((void *)(unsigned long long)free_str(&src));
	}
	return (dest);
}

int	free_str(void **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}
