/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:54:19 by habouda           #+#    #+#             */
/*   Updated: 2024/10/31 18:09:13 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int monitoring(t_data *data, t_philo *philo)
{
	int 	i;
	long	time;

	i = 0;
	while (1)
	{
		printf("aaaaaaaaaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		time = get_time() - data->time_start;
		if (time - philo[i].time_last_meal >= data->time_eat)
		{
			printf("%ld :%d has died\n",time , philo[i].id);
			i = 0;
			while (i < data->n_philo + 1)
			{
				time = get_time() - data->time_start;
				pthread_join(philo[i].thread, NULL);
				i++;
			}
			return (0);
		}
		i++;
		if (i < data->n_philo)
		{
			i = 0;
		}
	}
}
