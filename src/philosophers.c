/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:46:54 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/24 17:44:42 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_death_checker(t_table *t)
{
	int	i;

	num_of_eat_checker(t);
	while (!t->is_dead)
	{
		num_of_eat_checker(t);
		i = -1;
		while (++i < t->num_of_philo && !(t->is_dead))
		{
			pthread_mutex_lock(&t->meal_check);
			if (ft_time_diff(ft_get_time_in_ms(), t->philos[i].last_meal)
				> t->time_to_die)
			{
				ft_put_action(t, t->philos[i].id, "died");
				t->is_dead = true;
			}
			pthread_mutex_unlock(&t->meal_check);
			smart_sleep(100);
		}
	}
}

static void	ft_eat(t_philo *p)
{
	pthread_mutex_lock(&(p->table->forks[p->left_fork_id]));
	ft_put_action(p->table, p->id, "has taken a fork");
	pthread_mutex_lock(&(p->table->forks[p->right_fork_id]));
	ft_put_action(p->table, p->id, "has taken a fork");
	pthread_mutex_lock(&(p->table->meal_check));
	ft_put_action(p->table, p->id, "is eating");
	p->last_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(&(p->table->meal_check));
	smart_sleep(p->table->time_to_eat);
	p->table->all_ate++;
	pthread_mutex_unlock(&p->table->forks[p->left_fork_id]);
	pthread_mutex_unlock(&p->table->forks[p->right_fork_id]);
	if (!p->table->is_dead)
	{
		ft_put_action(p->table, p->id, "is sleeping");
		smart_sleep(p->table->time_to_sleep);
	}
}

static void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (!philo->table->is_dead)
	{
		num_of_eat_checker(philo->table);
		if (philo->table->is_dead)
			break ;
		ft_eat(philo);
		ft_put_action(philo->table, philo->id, "is thinking");
	}
	return (NULL);
}

int	philosophers(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = ft_get_time_in_ms();
	while (i < table->num_of_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philosopher_routine,
				&table->philos[i]))
			return (1);
		table->philos[i].last_meal = ft_get_time_in_ms();
		i++;
	}
	ft_death_checker(table);
	i = -1;
	while (++i < table->num_of_philo)
		pthread_join(table->philos[i].thread, NULL);
	return (0);
}
