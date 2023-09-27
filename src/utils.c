/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:41:44 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/27 19:29:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	ft_get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void		smart_sleep(u_int64_t time, t_table *t)
{
	u_int64_t	i;

	i = ft_get_time_in_ms();
	while (!(t->is_dead))
	{
		if (ft_time_diff(i, ft_get_time_in_ms()) >= time)
			break ;
		usleep(50);
	}
}

u_int64_t	ft_time_diff(u_int64_t past, u_int64_t pres)
{
	return (pres - past);
}

void	ft_put_action(t_table *t, int filo_id, char *str)
{
    pthread_mutex_lock(&t->writing);
    // pthread_mutex_lock(&t->dead_mutex);
    if (!t->is_dead)
    {
        printf("%ld %d %s\n",
            ft_get_time_in_ms() - t->start_time, filo_id + 1, str);
    }
    // pthread_mutex_unlock(&t->dead_mutex);
    pthread_mutex_unlock(&t->writing);
}

void	ft_num_of_eat_check(t_table *t)
{
	int	i;
	int flag;

	i = -1;
	flag = 0;
	while (++i < t->num_of_philo && !flag)
	{
		pthread_mutex_lock(&t->philos[i].x_eat_mutex);
		//pthread_mutex_lock(&t->dead_mutex);
		if (t->philos[i].x_eat != t->num_of_eat)
			flag = 1;
		else 
			t->is_dead = true;
		pthread_mutex_unlock(&t->philos[i].x_eat_mutex);
		//pthread_mutex_unlock(&t->dead_mutex);
	}
}
