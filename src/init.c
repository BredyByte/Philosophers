/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:08:50 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/19 18:34:09 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_arg_check(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	printf("OK\n");
	return (0);
}

int	ft_pcheck(t_philo *p, char **argv)
{
	if (p->num_of_philo < 2 || p->time_to_die < 0 || p->time_to_eat < 0
		|| p->time_to_sleep < 0 || p->num_of_eat < 0)
		return (1);
	if (argv[5])
	{
		if (p->num_of_eat < 0)
			return (1);
	}
	return (0);
}

int	ft_init_mutex(t_philo *p)
{
	int	i;

	i = 0;
	p->forks = (int *)malloc(sizeof(int) * p->num_of_philo);
	if (!p->forks)
	{
		printf("Error: malloc error\n");
		return (1);
	}
	while (i < p->num_of_philo)
	{
		if (pthread_mutex_init(&p->forks[i], NULL))
		{
			printf("Error: mutex init error\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_init(t_philo *p, int argc, char **argv)
{
	p = (t_philo *)malloc(sizeof(t_philo));
	if (!p)
	{
		printf("Error: malloc error\n");
		return (1);
	}
	p->num_of_philo = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		p->num_of_eat = ft_atoi(argv[5]);
	else
		p->num_of_eat = -1;
	if (ft_pcheck(p, argv))
		return (1);
	if (ft_init_mutex(p))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (ft_arg_check(argc))
		return (1);
	if (ft_init(&philo, argc, argv))
		return (1);
	return (0);
}
