/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:41:44 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/22 12:16:35 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleep(t_philo *p, int time)
{
	long long	start;

	start = ft_get_time_in_ms();
	while (ft_get_time_in_ms() - start < time && !p->table->is_dead)
		usleep(100);
}

int	ft_time_def(long long pres, long long past)
{
	return (pres - past);
}

void	ft_put_action(t_table *t, int filo_id, char *str)
{
	pthread_mutex_lock(&t->writing);
	if (!t->is_dead)
		printf("%lld %d %s\n", ft_get_time_in_ms() - t->start_time, filo_id,
			str);
	pthread_mutex_unlock(&t->writing);
}

long long	ft_get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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
