/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:14:50 by habouda           #+#    #+#             */
/*   Updated: 2024/11/10 21:16:30 by habouda          ###   ########.fr       */
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
    	pthread_mutex_lock(&philo->right_fork);
    	pthread_mutex_lock(philo->left_fork);
	}
}
