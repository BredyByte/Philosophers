/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:46:54 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/27 19:32:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void ft_eat(t_philo *p)
{
	pthread_mutex_lock(&(p->table->forks[p->left_fork_id]));
	ft_put_action(p->table, p->id, "has taken a fork");
	pthread_mutex_lock(&(p->table->forks[p->right_fork_id]));
    ft_put_action(p->table, p->id, "has taken a fork");
    pthread_mutex_lock(&(p->table->meal_check));
    ft_put_action(p->table, p->id, "is eating");
    p->last_meal = ft_get_time_in_ms();
    pthread_mutex_unlock(&(p->table->meal_check));
    smart_sleep(p->table->time_to_eat, p->table);
    pthread_mutex_lock(&(p->x_eat_mutex));
    p->x_eat++;
    pthread_mutex_unlock(&(p->x_eat_mutex));
	pthread_mutex_unlock(&p->table->forks[p->left_fork_id]);
	pthread_mutex_unlock(&p->table->forks[p->right_fork_id]);
}

static void	ft_eat_for_one(t_philo *p)
{
	pthread_mutex_lock(&(p->table->forks[p->left_fork_id]));
	ft_put_action(p->table, p->id, "has taken a fork");
	smart_sleep(p->table->time_to_die + 1, p->table);
	ft_put_action(p->table, p->id, "died");
	//pthread_mutex_lock(&(p->table->dead_mutex));
	p->table->is_dead = true;
	//pthread_mutex_unlock(&(p->table->dead_mutex));
}

static void	*philosopher_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2)
		usleep(15000);
	if (p->table->num_of_philo == 1)
		ft_eat_for_one(p);
	//pthread_mutex_lock(&(p->table->dead_mutex));
	while (!p->table->is_dead)
	{
		//pthread_mutex_unlock(&(p->table->dead_mutex));
		ft_eat(p);
		if (p->x_eat == p->table->num_of_eat)
			break ;
		ft_put_action(p->table, p->id, "is sleeping");
		smart_sleep(p->table->time_to_sleep, p->table);
		ft_put_action(p->table, p->id, "is  thinking");
		//pthread_mutex_unlock(&(p->table->dead_mutex));
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
