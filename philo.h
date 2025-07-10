/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:12:16 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/10 19:30:30 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

# define MALLOC_ERROR -1
# define ERROR -1
# define SUCCESS 0

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_arg_index
{
	PROGRAM = 0,
	N_PHILOS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	MEALS_TO_EAT, // optional
	ARG_MIN_COUNT = MEALS_TO_EAT,
	ARG_MAX_COUNT,
}	t_arg_index;

/* All the time values are in miliseconds */
typedef struct s_params
{
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	ssize_t	meals_to_eat;
}	t_params;

/* ate_at is in miliseconds */
typedef struct s_philo
{
	int				id;
	t_bool			is_alive;
	size_t			last_meal_time;
	size_t			meals_eaten;
	t_params		*params;
	pthread_mutex_t	*mutex;
}	t_philo;

typedef struct s_simulation
{
	size_t			n_philos;
	size_t			start_time;
	t_params		params;
	t_philo			*philos;
	t_bool			running;
	pthread_t		*threads;
	pthread_mutex_t	mutex;
}	t_simulation;

// time.c
size_t	now_in_ms(void);
size_t	time_in_ms(struct timeval *time);
size_t	msec_to_usec(size_t time_in_ms);

// utils.c
t_bool	is_valid_number(char *str);
int		ft_atoi(const char *nptr);

// actions.c
void	p_eat(t_philo *philo);
void	p_think(t_philo *philo);
void	p_sleep(t_philo *philo);
void	change_state(t_philo *philo);

#endif
