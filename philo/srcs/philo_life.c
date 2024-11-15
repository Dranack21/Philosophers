/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:19:37 by habouda           #+#    #+#             */
/*   Updated: 2024/11/15 01:03:37 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(1000);
	while (1)
	{
		if (eat(philo->data, philo) == EXIT_FAILURE)
			return (NULL);
		pthread_mutex_lock(&philo->eaten_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->eaten_mutex);
		if (sleepge(philo->data, philo) == EXIT_FAILURE)
			return (NULL);
		pthread_mutex_lock(&philo->life_mutex);
		if (philo->alive == 0)
		{
			pthread_mutex_unlock(&philo->life_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->life_mutex);
		while (philo->can_eat == 0 && philo->meals_eaten != philo->data->n_eat)
			usleep(50);
	}
	return (NULL);
}

int	eat(t_data *data, t_philo *philo)
{
	long	time;

	lock_forks(philo);
	pthread_mutex_lock(&philo->life_mutex);
	if (philo->alive == 0)
	{
		pthread_mutex_unlock(&philo->life_mutex);
		unlock_forks(philo);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->life_mutex);
	time = get_time() - data->time_start;
	pthread_mutex_lock(&philo->eat_mutex);
	philo->time_last_meal = time;
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld :%d has taken a fork\n", time, philo->id);
	printf("%ld :%d has taken a fork\n", time, philo->id);
	printf("%ld :%d is eating\n", time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
	if (action(data->time_eat, data, philo) == EXIT_FAILURE)
		return (unlock_forks(philo), EXIT_FAILURE);
	unlock_forks(philo);
	return (EXIT_SUCCESS);
}

int	sleepge(t_data *data, t_philo *philo)
{
	struct timeval	tv;
	long			time;

	pthread_mutex_lock(&philo->life_mutex);
	if (philo->alive == 0)
	{
		pthread_mutex_unlock(&philo->life_mutex);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&philo->life_mutex);
	gettimeofday(&tv, NULL);
	time = get_time() - data->time_start;
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld :%d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&data->print_mutex);
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
		pthread_mutex_lock(&philo->life_mutex);
		if (philo->alive == 0)
		{
			pthread_mutex_unlock(&philo->life_mutex);
			return (EXIT_FAILURE);
		}
		pthread_mutex_unlock(&philo->life_mutex);
	}
	return (EXIT_SUCCESS);
}
