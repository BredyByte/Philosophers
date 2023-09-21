/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:41:44 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/21 14:50:35 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_table *t)
{
	int	i;

	if (t->philos)
	{
		free(t->philos);
		t->philos = NULL;
	}
	if (t->forks)
	{
		i = 0;
		while (i < t->num_of_philo)
			pthread_mutex_destroy(&t->forks[i++]);
		free(t->forks);
		t->forks = NULL;
	}
}

void	ft_error(char *error)
{
	printf("%s", error);
	exit(1);
}
