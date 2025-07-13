/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:12:16 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/13 22:34:39 by fde-alme         ###   ########.fr       */
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
# include <stdbool.h>

# define MALLOC_ERROR -1
# define MUTEX_ERROR - 1
# define ERROR -1
# define SUCCESS 0

# define RESET "\033[0m"

# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

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

typedef enum e_state
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}	t_state;

typedef	struct s_table	t_table;
typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
	size_t	id;
	t_mutex	fork_mutex;
}	t_fork;

typedef struct s_philo
{
	int			id;
	size_t		last_meal_time;
	size_t		meals_eaten;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_table		*table;
	pthread_t	thread;
	t_mutex		meal_mutex;
	t_mutex		write_mutex;
}	t_philo;

struct s_table
{
	ssize_t		n_philos;
	size_t		start_time;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	ssize_t		meals_to_eat;
	bool		finished;
	t_philo		*philos;
	t_fork		*forks;
	t_mutex		simulation_mutex;
	pthread_t	monitor;
};

/* PROTOTYPES */

// main.c
void	free_table(t_table *table);

// time.c
size_t	now_in_ms(void);
size_t	time_in_ms(struct timeval *time);
size_t	msec_to_usec(size_t time_in_ms);

// init.c
void	init_data(t_table *table, char *argv[]);

// table.c
int		init_all_table(t_table *table, char *argv[]);
void	init_table(t_table *table, char *argv[]);
int		init_table_mutexes(t_table *table);
void	destroy_table_mutexes(t_table *table);
void	clean_table(t_table *table);

// philosophers.c
int		init_all_philos(t_table *table);
int		init_philosophers(t_table *table);
int		init_philosophers_mutexes(t_table *table);
void	destroy_philosophers_mutexes(t_table *table);
void	clean_philosophers(t_table *table);

// forks.c
int		init_all_forks(t_table *table);
int		init_forks(t_table *table);
int		init_forks_mutexes(t_table *table);
void	destroy_forks_mutexes(t_table *table);
void	clean_forks(t_table *table);

// utils.c
void	exit_error(const char *msg);
bool	is_valid_number(char *str);
int		ft_atoi(const char *nptr);

// actions.c
void	p_eat(t_philo *philo);
void	p_think(t_philo *philo);
void	p_sleep(t_philo *philo);

// monitor.c
void	init_monitor(pthread_t *monitor, t_table *table);

// setters_getters.c
void	set_bool(t_mutex *mutex, bool *dest, bool value);
bool	get_bool(t_mutex *mutex, bool *target);
void	set_size_t(t_mutex *mutex, size_t *dest, size_t value);
size_t	get_size_t(t_mutex *mutex, size_t *target);
bool	simulation_finished(t_table *table);

// write.c
void	write_status(t_philo *philo, t_state state);

#endif
