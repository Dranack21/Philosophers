/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:19:37 by habouda           #+#    #+#             */
/*   Updated: 2024/10/30 18:36:09 by habouda          ###   ########.fr       */
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
	philo->time_eat = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	time = philo->time_eat - data->time_start;
	printf("%ld :%d is eating\n",time , philo->id);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	return (EXIT_SUCCESS);
}