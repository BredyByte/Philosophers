/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:41:44 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/26 12:45:42 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	ft_get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_error("Error: gettimeofday\n", NULL, 1));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	smart_sleep(useconds_t time)
{
	u_int64_t	start;

	start = ft_get_time_in_ms();
	while ((ft_get_time_in_ms() - start) < time)
		usleep(time / 10);
}

int	ft_time_diff(u_int64_t past, u_int64_t pres)
{
	return (pres - past);
}

void	ft_put_action(t_table *t, int filo_id, char *str)
{
	pthread_mutex_lock(&t->writing);
	if (!t->is_dead)
	{
		printf("[\033[1;93m%06lld\033[0m]  \033[1;92m%03d  \033[1;95m%s\n\033[0m\n",
			ft_get_time_in_ms() - t->start_time, filo_id + 1, str);
	}
	pthread_mutex_unlock(&t->writing);
}

void	ft_num_of_eat_check(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->num_of_philo)
	{
		if (t->philos[i].x_eat != t->num_of_eat)
			return ;
	}
	t->is_dead = true;
}
