/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:41:44 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/24 17:26:28 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	ft_get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_error("Error: gettimeofday\n", NULL));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	smart_sleep(useconds_t time)
{
	u_int64_t	start;

	start = ft_get_time_in_ms();
	while ((ft_get_time_in_ms() - start) < time)
		usleep(time / 10);
}

int	ft_time_diff(u_int64_t pres, u_int64_t past)
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

void	num_of_eat_checker(t_table *t)
{
	if (t->num_of_eat == -1)
		return ;
	if (t->all_ate != (t->num_of_eat * t->num_of_philo))
		return ;
	t->is_dead = true;
	pthread_mutex_lock(&t->meal_check);
}
