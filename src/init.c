/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:08:50 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/22 12:58:36 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_mutex(t_table *t)
{
	int	i;

	t->forks = malloc(sizeof(pthread_mutex_t) * t->num_of_philo);
	if (!t->forks)
		return (1);
	i = 0;
	while (i < t->num_of_philo)
	{
		if (pthread_mutex_init(&t->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(t->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(t->meal_check), NULL))
		return (1);
	return (0);
}

static int	ft_init_philos(t_table *t)
{
	int	i;

	i = 0;
	t->philos = malloc(sizeof(t_philo) * t->num_of_philo);
	if (!t->philos)
		return (1);
	while (i < t->num_of_philo)
	{
		t->philos[i].id = i + 1;
		t->philos[i].left_fork_id = i;
		t->philos[i].right_fork_id = (i + 1) % t->num_of_philo;
		t->philos[i].table = t;
		t->philos[i].x_eat = 0;
		i++;
	}
	return (0);
}

int	ft_init(t_table *t, int argc, char **argv)
{
	t->num_of_philo = ft_atoi(argv[1]);
	t->time_to_die = ft_atoi(argv[2]);
	t->time_to_eat = ft_atoi(argv[3]);
	t->time_to_sleep = ft_atoi(argv[4]);
	t->start_time = 0;
	t->is_dead = false;
	if (argc == 6)
		t->num_of_eat = ft_atoi(argv[5]);
	else
		t->num_of_eat = -1;
	if (t->num_of_philo < 2 || t->time_to_die < 0 || t->time_to_eat < 0
		|| t->time_to_sleep < 0 || t->num_of_philo > 250)
		return (1);
	if (ft_init_mutex(t))
		return (1);
	if (ft_init_philos(t))
		return (1);
	return (0);
}

void	ft_eat(t_philo *p)
{
	pthread_mutex_lock(&p->table->forks[p->left_fork_id]);
	ft_put_action(p->table, p->id, "has taken a fork");
	pthread_mutex_lock(&p->table->forks[p->right_fork_id]);
	ft_put_action(p->table, p->id, "has taken a fork");
	pthread_mutex_lock(&(p->table->meal_check));
	ft_put_action(p->table, p->id, "is eating");
	p->last_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(&(p->table->meal_check));
	smart_sleep(p, p->table->time_to_eat);
	p->x_eat++;
	pthread_mutex_unlock(&p->table->forks[p->left_fork_id]);
	pthread_mutex_unlock(&p->table->forks[p->right_fork_id]);
}

void	num_of_eat_checker(t_table *t)
{
	int	i;

	if (t->num_of_eat == -1)
		return ;
	i = 0;
	while (i < t->num_of_philo)
	{
		if (t->philos[i].x_eat < t->num_of_eat)
			return ;
		i++;
	}
	t->is_dead = true;
	pthread_mutex_lock(&t->meal_check);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(15000);
	while (!philo->table->is_dead)
	{
		ft_eat(philo);
		num_of_eat_checker(philo->table);
		if (philo->table->is_dead)
			break ;
		ft_put_action(philo->table, philo->id, "is sleeping");
		smart_sleep(philo, philo->table->time_to_sleep);
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
	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (ft_arg_checker(argc, argv))
		ft_error("Arguments error\n");
	if (ft_init(&table, argc, argv))
		ft_error("Init error\n");
	if (philosophers(&table))
		ft_error("Philosophers error\n");
	ft_free(&table);
	return (0);
}
