/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbignon <cbignon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:27:03 by cbignon           #+#    #+#             */
/*   Updated: 2022/01/18 12:07:54 by cbignon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

# define UINT_MAX_STR "4294967295"

# define LOCK 1
# define FREE 0

typedef pthread_mutex_t	t_mutex;

typedef struct s_mut
{
	t_mutex	mut;
	int		state;
}	t_mut;

typedef struct s_arg
{
	int		nb_philo;
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		nb_meals;
	long	start;
	int		on;
	t_mutex	arg_mutex;
	t_mutex	print_mutex;
}	t_arg;

typedef struct s_philo
{
	pthread_t	tid;
	long		start;
	int			index;
	int			live;
	int			hungry;
	long		last_meal;
	int			meals_count;
	t_mutex		count_mut;
	t_mut		*fork;
	t_mut		*friends_fork;
	t_arg		*args;
}	t_philo;

typedef struct s_data
{
	long	start;
	t_arg	*args;
	t_philo	*philo;
	t_mut	*forks;
}	t_data;

void	*try_to_malloc(void *src, int size);
int		ft_atoui(char *arg);
int		is_digit(char c);
int		free_str(void **str);
int		ft_strlen(char *str);

int		parse_arg(char **arg, int c);
int		check_limits(char *arg);
int		check_values(t_arg *arg);

long	get_moment(long start);
long	get_time(void);
void	ft_usleep(long int usec);

int		init_struc(t_data *data, int argc, char **argv);
int		init_arg(t_data *data, int argc, char **argv);
int		init_philo(t_data *data);
int		init_forks(t_data *data);
int		attribute_forks(t_data *data);

int		print_status(t_philo *philo, char *status);
void	print_death(t_philo *philo);
int		print_error(char *message);

int		create_thread(t_data *data);
void	*god_ft(void *data);
void	*philo_ft(void *philo);

int		drop_forks(t_philo *philo);
int		change_fork_state(t_mut *fork, int before, int after);

int		philo_take_forks(t_philo *philo);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);

int		check_philosophers(t_data *data);
int		check_death(t_philo *philo, t_data *data, int n);
int		check_hungry(t_philo *philo, t_data *data, int n);

int		clean_all(t_data *data);
int		clean_args(t_arg *arg);
int		clean_philo(t_philo *philo);
int		clean_forks(t_mut *forks);

#endif
