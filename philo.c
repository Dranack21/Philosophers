/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:32:18 by habouda           #+#    #+#             */
/*   Updated: 2024/10/28 23:54:23 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_philo(t_data *data, t_philo *philo, char *argv[])
{
	int i;

	i = 0;
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->n_eat = ft_atoi(argv[5]);
	while (i++ != data->n_philo)
	{
		philo[i].id = i;
		philo[i].meal_count = 0;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		pthread_mutex_init(&philo[i].right_fork, NULL);
		if (i != 0)
			philo[i].left_fork = &philo[i-1].right_fork;
	}
	philo[0].left_fork = &philo[i-1].right_fork;
	return (0);
}


int create_philos(t_data *data, char *argv[])
{
	data->n_philo = ft_atoi(argv[1]);
	data->philo = malloc(sizeof(t_philo)* data->n_philo);
	init_philo(data, data->philo);
	return (0);
}

int parsing(int argc, char *argv[])
{
	int i;
	int j;

	j = 0;
	i = 1;
	if (argc != 5 && argc != 6)
		return (write(2, "Wrong number of arguments\n", 27), 1);
	while (i != argc)
	{
		if (argv[i][j])
		{
			while (argv[i][j])
			{
				if (ft_isdigit(argv[i][j]) == 1)
					j++;
				else
					return (write(2, "Wrong arguments\n", 17), 1);
			}
		}
		i++;
	}
	return(0);
}

int main(int argc, char *argv[])
{
	t_data data;

	if (parsing(argc, argv) == 1)
		return (1);
	create_philos(&data, argv);
}
