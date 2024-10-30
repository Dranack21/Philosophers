/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:53:35 by habouda           #+#    #+#             */
/*   Updated: 2024/10/30 15:36:22 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_threads(t_data *data ,t_philo *philo)
{
	int i;
	int result;

	i = 0;
	while(i != data->n_philo - 1)
	{
		result = pthread_create(&philo[i].thread, NULL, routine, (void*)(philo));
		if (result != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	sign = 1;
	i = 0;
	result = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if ((nptr[i] == '-' || nptr[i] == '+') && nptr[i])
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] && (ft_isdigit(nptr[i]) == 1))
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

int	ft_isdigit(int c)
{
	if (c < 58 && c > 47)
		return (1);
	else
		return (0);
}
