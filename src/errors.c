/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:33:38 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/27 18:16:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_clear_data(t_table	*t)
{
	if (t->forks)
		free(t->forks);
	if (t->philos)
		free(t->philos);
}

void	ft_exit(t_table *t)
{
	int	i;

	i = -1;
	if (t->forks)
	{
		while (++i < t->num_of_philo)
		{
			pthread_mutex_destroy(&t->forks[i]);
			pthread_mutex_destroy(&t->philos[i].x_eat_mutex);
		}
		pthread_mutex_destroy(&t->meal_check);
		pthread_mutex_destroy(&t->writing);
		pthread_mutex_destroy(&t->dead_mutex);
	}
	ft_clear_data(t);
}

int	ft_error(char *str, t_table *t, int flag)
{
	printf("%s\n", str);
	if (flag)
		ft_exit(t);
	else
		(void) t;
	exit(1);
}
