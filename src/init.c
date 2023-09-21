/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:08:50 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/21 16:46:24 by dbredykh         ###   ########.fr       */
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

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->forks[philo->id - 1]);
	usleep(philo->table->time_to_sleep);
	printf("%d %d thinking\n", philo->table->start_time, philo->id);
	philo->table->start_time += philo->table->time_to_sleep;
	pthread_mutex_unlock(&philo->table->forks[philo->id
		% philo->table->num_of_philo]);
	return (NULL);
}

void	philosophers(t_table *table)
{
	int	i;

	for (i = 1; i < table->num_of_philo; i++)
		pthread_mutex_lock(&table->forks[i]);
	while (table->num_of_eat-- != 0)
	{
		i = 0;
		while (i < table->num_of_philo)
		{
			table->philos[i].table = table;
			pthread_create(&table->philos[i].thread, NULL, philosopher_routine,
				&table->philos[i]);
			i++;
		}
	}
	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (ft_arg_checker(argc, argv))
		ft_error("Arguments error\n");
	if (ft_init(&table, argc, argv))
		ft_error("Init error\n");
	philosophers(&table);
	ft_free(&table);
	return (0);
}
