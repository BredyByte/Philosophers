/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:30:25 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/25 16:50:30 by dbredykh         ###   ########.fr       */
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
	u_int64_t	last_meal;
	int			x_eat;
	t_table		*table;
}				t_philo;

struct s_table
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	bool			is_dead;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	writing;
	int				check;
};

// libft.c

int			ft_isdigit(int c);
int			ft_atoi(const char *str);

// ft_arg_checker.c

int			ft_arg_checker(int argc, char **argv);

// utils.c
u_int64_t	ft_get_time_in_ms(void);
void		ft_put_action(t_table *t, int filo_id, char *str);
int			ft_time_diff(u_int64_t pres, u_int64_t past);
void		smart_sleep(useconds_t time);

// errors.c

void		ft_exit(t_table *t);
int			ft_error(char *str, t_table *t, int flag);

// philosophers.c

int			philosophers(t_table *table);

#endif
