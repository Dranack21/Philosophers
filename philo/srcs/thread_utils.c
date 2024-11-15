/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:14:50 by habouda           #+#    #+#             */
/*   Updated: 2024/11/15 01:13:16 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
}

void	unlock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
	}
}

void	wait_for_eat(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->eaten_mutex);
		if (philo->can_eat == 0 && philo->meals_eaten != philo->data->n_eat)
		{
			usleep(50);
			pthread_mutex_unlock(&philo->eaten_mutex);
		}
		else
			pthread_mutex_unlock(&philo->eaten_mutex);
	}
}
