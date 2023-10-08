/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:58:48 by marvin            #+#    #+#             */
/*   Updated: 2023/10/08 18:56:06 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philosopher_status(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->num_of_philo)
	{
		pthread_mutex_lock(&t->meal_check);
		if ((int)(ft_time_diff(t->philos[i].last_meal,
				ft_get_time_in_ms())) > t->time_to_die)
		{
			pthread_mutex_unlock(&t->meal_check);
			ft_put_action(t, t->philos[i].id, "died");
			pthread_mutex_lock(&t->dead_mutex);
			t->is_dead = 1;
			return (pthread_mutex_unlock(&t->dead_mutex), 1);
		}
		pthread_mutex_unlock(&t->meal_check);
	}
	return (0);
}

void	ft_death_checker(t_table *t)
{
	while (1)
	{
		pthread_mutex_lock(&t->dead_mutex);
		if (t->is_dead)
		{
			pthread_mutex_unlock(&t->dead_mutex);
			return ;
		}
		pthread_mutex_unlock(&t->dead_mutex);
		if (check_philosopher_status(t))
			return ;
		if (t->num_of_eat != -1)
			if (ft_num_of_eat_check(t))
				return ;
	}
}
