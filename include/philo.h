/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:30:25 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/21 16:07:09 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	int			left_fork_id;
	int			right_fork_id;
	t_table		*table;
}				t_philo;

struct s_table
{
	int				start_time;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	writing;
};

// libft.c

int		ft_isdigit(int c);
int		ft_atoi(const char *str);

// ft_arg_checker.c

int		ft_arg_checker(int argc, char **argv);

// utils.c
void	ft_free(t_table *t);
void	ft_error(char *error);

#endif
