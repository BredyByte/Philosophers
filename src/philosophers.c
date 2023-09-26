/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:46:54 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/26 12:44:59 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_death_checker(t_table *t)
{
	int	i;

	while (!t->is_dead)
	{
		i = -1;
		while (++i < t->num_of_philo && !(t->is_dead))
		{
			pthread_mutex_lock(&t->meal_check);
			if (ft_time_diff(t->philos[i].last_meal, ft_get_time_in_ms())
				> t->time_to_die)
			{
				ft_put_action(t, t->philos[i].id, "died 🥀");
				t->is_dead = true;
			}
			pthread_mutex_unlock(&t->meal_check);
		}
		ft_num_of_eat_check(t);
	}
}

static void	ft_eat(t_philo *p)
{
	pthread_mutex_lock(&(p->table->forks[p->left_fork_id]));
	ft_put_action(p->table, p->id, "has taken a fork 🍴");
	pthread_mutex_lock(&(p->table->forks[p->right_fork_id]));
	ft_put_action(p->table, p->id, "has taken a fork 🍴");
	pthread_mutex_lock(&(p->table->meal_check));
	ft_put_action(p->table, p->id, "is eating 🍝");
	p->last_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(&(p->table->meal_check));
	smart_sleep(p->table->time_to_eat);
	p->x_eat++;
	pthread_mutex_unlock(&p->table->forks[p->left_fork_id]);
	pthread_mutex_unlock(&p->table->forks[p->right_fork_id]);
}

static void	ft_eat_for_one(t_philo *p)
{
	pthread_mutex_lock(&(p->table->forks[p->left_fork_id]));
	ft_put_action(p->table, p->id, "has taken a fork 🍴");
	smart_sleep(p->table->time_to_die);
	ft_put_action(p->table, p->id, "died 🥀");
	p->table->is_dead = true;
}

static void	*philosopher_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2)
		usleep(15000);
	if (p->table->num_of_philo == 1)
		ft_eat_for_one(p);
	while (!p->table->is_dead)
	{
		ft_eat(p);
		if (p->x_eat == p->table->num_of_eat)
			break ;
		ft_put_action(p->table, p->id, "is sleeping 💤");
		smart_sleep(p->table->time_to_sleep);
		ft_put_action(p->table, p->id, "is  thinking 💭");
	}
	return (NULL);
}

int	philosophers(t_table *table)
{
	int	i;

	i = -1;
	table->start_time = ft_get_time_in_ms();
	while (++i < table->num_of_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philosopher_routine,
				&table->philos[i]))
			return (1);
	}
	ft_death_checker(table);
	i = -1;
	while (++i < table->num_of_philo)
		if (pthread_join(table->philos[i].thread, NULL))
			return (1);
	return (0);
}
