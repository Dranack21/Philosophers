/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:54:19 by habouda           #+#    #+#             */
/*   Updated: 2024/11/10 22:05:45 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_data *data, t_philo *philo)
{
	int		i;
	long	time;

	i = 0;
	usleep(1000);
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{
			time = get_time() - data->time_start;
			pthread_mutex_lock(&philo[i].eat_mutex);
			if (time - philo[i].time_last_meal >= data->time_die)
			{
				pthread_mutex_lock(&philo[i].life_mutex);
				philo[i].alive = 0;
				pthread_mutex_unlock(&philo[i].life_mutex);
				printf("%ld :%d has died\n", time, philo[i].id);
			}
			pthread_mutex_unlock(&philo[i].eat_mutex);
			i++;
			if (check_alive(data, philo) == 0 || check_eating(data, philo) == 0)
				return (0);
		}
	}
}

int	check_eating(t_data *data, t_philo *philo)
{
	int	i;
	int	all_full;

	if (data->n_eat == -1)
		return (1);
	all_full = 1;
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&philo[i].eat_mutex);
		if (philo[i].meals_eaten < data->n_eat)
			all_full = 0;
		pthread_mutex_unlock(&philo[i].eat_mutex);
		i++;
	}
	if (all_full)
	{
		set_all_deadge(data, philo);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	check_alive(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&philo[i].life_mutex);
		if (philo[i].alive == 0)
		{
			pthread_mutex_unlock(&philo[i].life_mutex);
			set_all_deadge(data, philo);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].life_mutex);
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
		pthread_mutex_lock(&philo[i].life_mutex);
		philo[i].alive = 0;
		pthread_mutex_unlock(&philo[i].life_mutex);
		i++;
	}
	return (0);
}
