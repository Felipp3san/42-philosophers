/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:50:14 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/22 19:17:28 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

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

typedef enum e_bool
{
	FALSE,
	TRUE	
}	t_bool;

typedef	struct s_table t_table;
typedef pthread_mutex_t t_mutex;
typedef unsigned long long t_ull;

typedef struct s_fork
{
	size_t	id;
	t_mutex	fork_mutex;
}	t_fork;

typedef struct s_times
{
	t_ull	start_time;
	t_ull	time_to_die;
	t_ull	time_to_eat;
	t_ull	time_to_sleep;
}	t_times;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	t_ull		last_meal;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_times		*times;
	t_table		*table;
	t_mutex		meal_mutex;
	t_mutex		write_mutex;
	pthread_t	thread;
}	t_philo;

struct s_table
{
	int			n_philos;
	int			meals_to_eat;
	int			threads_running;
	t_bool		threads_ready;
	t_bool		finished;
	t_philo		*philos;
	t_fork		*forks;
	t_times		times;
	t_mutex		table_mutex;
	pthread_t	monitor;
};

#endif
