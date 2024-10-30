/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 22:53:35 by habouda           #+#    #+#             */
/*   Updated: 2024/10/30 18:02:06 by habouda          ###   ########.fr       */
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
	return (EXIT_SUCCESS);
}