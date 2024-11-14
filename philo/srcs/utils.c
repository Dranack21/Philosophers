/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:53:35 by habouda           #+#    #+#             */
/*   Updated: 2024/11/14 17:28:43 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	parsing(int argc, char *argv[])
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (write(2, "Wrong number of arguments\n", 27), EXIT_FAILURE);
	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '\0')
			return (write(2, "Empty argument\n", 15), EXIT_FAILURE);
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (write(2, "Wrong arguments\n", 17), EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

long	get_time(void)
{
	struct timeval	tv;
	long			value;

	gettimeofday(&tv, NULL);
	value = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (value);
}

void	one_philo(t_data *data)
{
	printf("0 :1 has taken a fork\n");
	usleep(data->time_die * 1000);
	printf("%ld :1 died\n", get_time() - data->time_start);
}
