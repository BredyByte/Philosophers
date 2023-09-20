/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:08:50 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/20 16:18:58 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_mutex(t_table *t)
{
	int	i;

	t->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* t->num_of_philo);
	if (!t->forks)
	{
		printf("Error: wrong of memmory allocation for forks\n");
		return (1);
	}
	i = 0;
	while (i < t->num_of_philo)
	{
		if (pthread_mutex_init(&t->forks[i], NULL) != 0)
		{
			printf("Error: wrong of mutex initialization\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_init_philos(t_table *t)
{
	int	i;

	t->philos = (t_philo *)malloc(sizeof(t_philo) * t->num_of_philo);
	if (!t->philos)
	{
		printf("Error: wrong of memmory allocation for philos\n");
		return (1);
	}
	i = 0;
	while (i < t->num_of_philo)
	{
		t->philos[i].id = i + 1;
		t->philos[i].left_fork = &t->forks[i];
		t->philos[i].right_fork = &t->forks[(i + 1) % t->num_of_philo];
		i++;
	}
	return (0);
}

int	ft_init(t_table *t, int argc, char **argv)
{
	t = (t_table *)malloc(sizeof(t_table));
	if (!t)
	{
		printf("Error: malloc error\n");
		return (1);
	}
	t->num_of_philo = ft_atoi(argv[1]);
	t->time_to_die = ft_atoi(argv[2]);
	t->time_to_eat = ft_atoi(argv[3]);
	t->time_to_sleep = ft_atoi(argv[4]);
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

int	main(int argc, char **argv)
{
	t_table	table;

	if (ft_arg_checker(argc, argv))
		ft_error ("Arguments error\n", NULL);
	if (ft_init(&table, argc, argv))
		ft_error ("Init error\n", &table);
	return (0);
}
