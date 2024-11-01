/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:32:18 by habouda           #+#    #+#             */
/*   Updated: 2024/10/31 18:54:33 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void* arg)
{
	t_philo *philo;
	// t_data	*data;

	philo = (t_philo*)arg;
	// data = philo->data;
	if (philo->id % 2 == 1)
		usleep(50);
	while (1)
	{
		eat(philo->data, philo);
		sleepge(philo->data, philo);
	}
	return (NULL);
}

int	init_philo(t_data *data, t_philo *philo, char *argv[])
{
	int	i;

	i = 0;
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->n_eat = ft_atoi(argv[5]);
	while (i < data->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].meal_count = 0;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		philo[i].alive = 1;
		philo[i].data = data;
		if (pthread_mutex_init(&philo[i].right_fork, NULL) != EXIT_SUCCESS) 
			return (EXIT_FAILURE);
		if (i != 0)
			philo[i].left_fork = &philo[i - 1].right_fork;
		i++;
	}
	philo[0].left_fork = &philo[data->n_philo - 1].right_fork;
	return (EXIT_SUCCESS);
}

int create_threads(t_data *data ,t_philo *philo)
{
	int i;

	i = 0;
	while(i != data->n_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &(philo[i])) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	monitoring(data, philo);
	while (i < data->n_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	create_philos(t_data *data, char *argv[])
{
	int 			i;
	struct timeval tv;
	i = 0;

	gettimeofday(&tv, NULL);
	data->time_start = get_time();
	data->n_philo = ft_atoi(argv[1]);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return (EXIT_FAILURE);
	if (init_philo(data, data->philo, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	create_threads(data, data->philo);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (parsing(argc, argv) == 1)
		return (EXIT_FAILURE);
	create_philos(&data, argv);
}
