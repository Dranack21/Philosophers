/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:32:18 by habouda           #+#    #+#             */
/*   Updated: 2024/10/27 20:27:12 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int i = 2;

// void *routine2()
// {
// 	printf("test from threads\n");
// 	sleep(3);
// 	i++;
// 	printf("%d\n", i);
// 	return (NULL);
// }

// void *routine()
// {
// 	printf("test from threads\n");
// 	sleep(3);
// 	i++;
// 	printf("%d\n", i);
// 	return (NULL);
// }

// int main()
// {
// 	pthread_t t1;
// 	pthread_t t2;
// 	pthread_mutex_t lock;
	
// 	pthread_mutex_init(&lock, NULL);
// 	pthread_create(&t1, NULL, &routine, NULL);
// 	pthread_create(&t2, NULL, &routine2, NULL);
// 	pthread_join(t1, NULL);
// 	pthread_join(t1, NULL);
// 	return (0);
// }

int	ft_isdigit(int c)
{
	if (c < 58 && c > 47)
		return (0);
	else
		return (1);
}

int create_philos()
{
	
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
				if (ft_isdigit(argv[i][j]) == 0)
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
	if (parsing(argc, argv) == 1)
		return (1);
	create_philos(argv[1]);
}
