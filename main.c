/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:42:55 by cbignon           #+#    #+#             */
/*   Updated: 2022/01/11 14:12:25 by cbignon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("Please enter valid number of arguments\n");
		return (-1);
	}
	if (parse_arg(argv, argc))
	{
		printf("Please enter only positiv numbers, from 1 to U INT MAX\n");
		return (-1);
	}
	data = try_to_malloc(data, sizeof(t_data));
	if (!data)
		return (-1);
	if (init_struc(data, argc, argv))
		return (-1);
	create_thread(data);
	clean_all(data);
	return (0);
}
