/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:54:19 by habouda           #+#    #+#             */
/*   Updated: 2024/11/15 01:12:56 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_data *data, t_philo *philo)
{
	int		i;
	long	time;

	while (1)
	{
		i = -1;
		while (++i < data->n_philo)
		{
			time = get_time() - data->time_start;
			pthread_mutex_lock(&philo[i].eat_mutex);
			if (time - philo[i].time_last_meal >= data->time_die)
			{
				pthread_mutex_lock(&philo[i].life_mutex);
				philo[i].alive = 0;
				pthread_mutex_unlock(&philo[i].life_mutex);
				pthread_mutex_lock(&data->print_mutex);
				printf("%ld :%d has died\n", time, philo[i].id);
				pthread_mutex_unlock(&data->print_mutex);
			}
			pthread_mutex_unlock(&philo[i].eat_mutex);
			if (check_alive(data, philo) == 0 || check_eating(data, philo) == 0
				|| can_eat(data, philo) == 0)
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

int	can_eat(t_data *data, t_philo *philo)
{
	int	i;
	int	min_meals;

	i = -1;
	min_meals = philo[1].meals_eaten;
	while (++i < data->n_philo)
	{
		pthread_mutex_lock(&philo[i].eaten_mutex);
		if (philo[i].meals_eaten < min_meals)
			min_meals = philo[i].meals_eaten;
		pthread_mutex_unlock(&philo[i].eaten_mutex);
	}
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&philo[i].eaten_mutex);
		if (philo[i].meals_eaten == min_meals
			&& (data->n_eat == -1 || philo[i].meals_eaten < data->n_eat))
			philo[i].can_eat = 1;
		else
			philo[i].can_eat = 0;
		pthread_mutex_unlock(&philo[i].eaten_mutex);
		i++;
	}
	return (1);
}
