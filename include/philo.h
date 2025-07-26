/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:12:16 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/23 14:14:43 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "types.h"

/* PROTOTYPES */

// utils.c
void	check_params(char *argv[]);
void	free_table(t_table *table);
void	exit_error(const char *msg);
void	log_debug(t_table *table, const char *color, const char *msg, int *id);

// extra_functions.c
void	ft_usleep(t_ull usec);
int		ft_atoi(const char *nptr);
t_bool	is_valid_number(char *str);

// threads.c
void	join_threads(t_table *table);
void	init_philos_threads(t_table *table);
void	init_monitor_thread(t_table *table);

// routine.c
void	*lone_philo_routine(void *philosopher);
void	*philo_routine(void *philosopher);

// time_utils.c
t_ull	time_to_msec(struct timeval *time);
t_ull	time_to_usec(struct timeval *time);
t_ull	now_in_ms(void);
t_ull	now_in_usec(void);
t_ull	msec_to_usec(t_ull time_in_ms);

// init.c
void	init_data(t_table *table, char *argv[]);

// syncro_utils.c
t_bool	all_threads_ready(t_table *table);
t_bool	all_threads_running(t_table *table);

// table.c
void	init_table(t_table *table, char *argv[]);
int		init_table_mutexes(t_table *table);
void	destroy_table_mutexes(t_table *table);
void	clean_table(t_table *table);

// philosophers.c
int		init_philosophers(t_table *table);
int		init_philosophers_mutexes(t_table *table);
void	destroy_philosophers_mutexes(t_table *table);
void	clean_philosophers(t_table *table);

// forks.c
int		init_forks(t_table *table);
int		init_forks_mutexes(t_table *table);
void	destroy_forks_mutexes(t_table *table);
void	clean_forks(t_table *table);

// actions.c
void	p_eat(t_philo *philo);
void	p_think(t_philo *philo);
void	p_sleep(t_philo *philo);

// monitor.c
void	*monitor(void *data);

// getters.c
int		get_int(t_mutex *mutex, int *target);
t_ull	get_ull(t_mutex *mutex, t_ull *target);
t_bool	get_bool(t_mutex *mutex, t_bool *target);
t_bool	simulation_finished(t_table *table);

// setters.c
void	set_int(t_mutex *mutex, int *dest, int value);
void	set_ull(t_mutex *mutex, t_ull *dest, t_ull value);
void	set_bool(t_mutex *mutex, t_bool *dest, t_bool value);
void	increase_int(t_mutex *mutex, int *dest);

// write.c
void	write_status(t_philo *philo, t_state state);

#endif
