/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:19:37 by habouda           #+#    #+#             */
/*   Updated: 2024/10/31 16:43:21 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_data *data, t_philo *philo)
{
	struct timeval tv;
	long 	time;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->right_fork);
	gettimeofday(&tv ,NULL);
	time = get_time() - data->time_start;
	printf("%ld :%d has taken a fork\n",time , philo->id);
	printf("%ld :%d has taken a fork\n",time , philo->id);
	printf("%ld :%d is eating\n",time , philo->id);
	philo->eating = 1;
	usleep(data->time_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	philo->meals_eaten++;
	philo->eating = 0;
	return (EXIT_SUCCESS);
}

int sleepge(t_data *data, t_philo *philo)
{
	struct timeval tv;
	long 	time;

	gettimeofday(&tv ,NULL);
	time = get_time() - data->time_start;
	printf("%ld :%d is sleeping\n",time , philo->id);
	usleep(data->time_sleep * 1000);
	printf("%ld :%d is thinking\n",time , philo->id);
	return(EXIT_SUCCESS);
}