/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbredykh <dbredykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:44:13 by dbredykh          #+#    #+#             */
/*   Updated: 2023/09/20 15:52:04 by dbredykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_positive_number(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_arg_checker(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!ft_is_positive_number(argv[i]))
			return (1);
		i++;
	}
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (1);
	return (0);
}
