/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:33:38 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/25 14:00:41 by dbredykh         ###   ########.fr       */
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
			pthread_mutex_destroy(&t->forks[i++]);
		pthread_mutex_destroy(&t->meal_check);
		pthread_mutex_destroy(&t->writing);
	}
	ft_clear_data(t);
}

int	ft_error(char *str, t_table *t)
{
	printf("%s\n", str);
	if (t)
		ft_exit(t);
	return (1);
}
