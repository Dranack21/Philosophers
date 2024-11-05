/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:54:19 by habouda           #+#    #+#             */
/*   Updated: 2024/11/03 17:23:05 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_data *data, t_philo *philo)
{
	int		i;
	long	time;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{
			time = get_time() - data->time_start;
			if (time - philo[i].time_last_meal >= data->time_die)
			{
				philo[i].alive = 0;
				printf("%ld :%d has died\n", time, philo[i].id);
			}
			i++;
			if (check_alive(data, philo) == 0)
				return (0);
		}
	}
}

int	check_alive(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (philo[i].alive == 0)
		{
			set_all_deadge(data, philo);
			return (0);
		}
		i++;
	}
	return (1);
}

int	set_all_deadge(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		philo[i].alive = 0;
		i++;
	}
	return (0);
}
