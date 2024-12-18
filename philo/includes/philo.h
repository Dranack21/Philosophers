/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:49:43 by habouda           #+#    #+#             */
/*   Updated: 2024/11/15 01:02:06 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	life_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	eaten_mutex;
	struct s_data	*data;
	long			time_death;
	long			time_sleep;
	long			time_eat;
	int				time_last_meal;
	int				id;
	int				meal_count;
	int				eating;
	int				can_eat;
	int				alive;
	int				meals_eaten;

}					t_philo;

typedef struct s_data
{
	t_philo			*philo;
	long			time_start;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_eat;
	int				n_philo;
	pthread_mutex_t	print_mutex;
}					t_data;

int					parsing(int argc, char *argv[]);
int					create_philos(t_data *data, char *argv[]);
int					init_philo(t_data *data, t_philo *philo);
void				*routine(void *arg);
int					eat(t_data *data, t_philo *philo);
long				get_time(void);
int					monitoring(t_data *data, t_philo *philo);
int					check_alive(t_data *data, t_philo *philo);
int					action(long desired_time, t_data *data, t_philo *philo);
int					set_all_deadge(t_data *data, t_philo *philo);
int					check_eating(t_data *data, t_philo *philo);
void				lock_forks(t_philo *philo);
void				unlock_forks(t_philo *philo);
void				one_philo(t_data *data);
int					can_eat(t_data *data, t_philo *philo);
void				wait_for_eat(t_philo *philo);

int					ft_isdigit(int c);
int					sleepge(t_data *data, t_philo *philo);
int					create_threads(t_data *data, t_philo *philo);
int					ft_atoi(const char *nptr);

#endif