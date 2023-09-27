/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 18:58:48 by marvin            #+#    #+#             */
/*   Updated: 2023/09/27 19:26:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void check_philosopher_status(t_table *t)
{
    int i = -1;

    while (++i < t->num_of_philo && !(t->is_dead))
    {
        pthread_mutex_lock(&t->meal_check);
        if ((int)(ft_time_diff(t->philos[i].last_meal, ft_get_time_in_ms())) > t->time_to_die)
        {
            //pthread_mutex_lock(&t->dead_mutex);
            ft_put_action(t, t->philos[i].id, "died");
            t->is_dead = true;
            //pthread_mutex_unlock(&t->dead_mutex);
        }
        pthread_mutex_unlock(&t->meal_check);
    }
}

void ft_death_checker(t_table *t)
{
    while (true)
    {
        // pthread_mutex_lock(&t->dead_mutex);
        if (t->is_dead)
        {
           // pthread_mutex_unlock(&t->dead_mutex);
            break;
        }
        // pthread_mutex_unlock(&t->dead_mutex);
        check_philosopher_status(t);
        ft_num_of_eat_check(t);
    }
}
