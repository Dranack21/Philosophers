/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:32:18 by habouda           #+#    #+#             */
/*   Updated: 2024/11/10 21:08:28 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_data *data, t_philo *philo, char *argv[])
{
	int	i;

	i = 0;
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->n_eat = ft_atoi(argv[5]);
	else 
		data->n_eat = -1;
	while (i < data->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].meal_count = 0;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		philo[i].alive = 1;
		philo[i].data = data;
		philo[i].time_last_meal = 0;
		if (pthread_mutex_init(&philo[i].right_fork, NULL) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (pthread_mutex_init(&philo[i].eat_mutex, NULL) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (pthread_mutex_init(&philo[i].life_mutex, NULL) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (i != 0)
			philo[i].left_fork = &philo[i - 1].right_fork;
		i++;
	}
	philo[0].left_fork = &philo[data->n_philo - 1].right_fork;
	return (EXIT_SUCCESS);
}

void cleanup(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(philo[i].left_fork);
		i++;
	}
	free (philo);
}
int	create_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i != data->n_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &(philo[i])) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	monitoring(data, philo);
	while (i < data->n_philo)
	{
		// printf("philo %d meals eaten %d\n", philo[i].id, philo[i].meals_eaten);
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	create_philos(t_data *data, char *argv[])
{
	struct timeval	tv;

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
	cleanup(&data, data.philo);
}