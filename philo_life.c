/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:19:37 by habouda           #+#    #+#             */
/*   Updated: 2024/11/07 21:33:44 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(50);
	while (1)
	{
		if (eat(philo->data, philo) == EXIT_FAILURE)
			return (NULL);
		if (sleepge(philo->data, philo) == EXIT_FAILURE)
			return (NULL);
		if (philo->alive == 0)
			return (NULL);
	}
	return (NULL);
}

int	eat(t_data *data, t_philo *philo)
{
	struct timeval	tv;
	long			time;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->right_fork);
	if (philo->alive == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
	gettimeofday(&tv, NULL);
	time = get_time() - data->time_start;
	printf("%ld :%d has taken a fork\n", time, philo->id);
	printf("%ld :%d has taken a fork\n", time, philo->id);
	printf("%ld :%d is eating\n", time, philo->id);
	philo->eating = 1;
	philo->time_last_meal = time;
	if (action(data->time_eat, data, philo) == EXIT_FAILURE)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	philo->meals_eaten++;
	philo->eating = 0;
	return (EXIT_SUCCESS);
}

int	sleepge(t_data *data, t_philo *philo)
{
	struct timeval	tv;
	long			time;

	if (philo->alive == 0)
		return(EXIT_FAILURE);
	gettimeofday(&tv, NULL);
	time = get_time() - data->time_start;
	printf("%ld :%d is sleeping\n", time, philo->id);
	if (action(data->time_sleep, data, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	time = get_time() - data->time_start;
	printf("%ld :%d is thinking\n", time, philo->id);
	return (EXIT_SUCCESS);
}

int	action(long desired_time, t_data *data, t_philo *philo)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = get_time() - data->time_start;
	desired_time += time;
	while (time < desired_time)
	{
		usleep(10);
		time = get_time() - data->time_start;
		if (philo->alive == 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}