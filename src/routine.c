/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:50:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/23 13:52:31 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lone_philo_routine(void *philosopher)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *) philosopher;
	table = (t_table *) philo->table;
	if (DEBUG == 1)
		printf(YELLOW"[DEBUG] Philosopher %d ready!"RESET"\n", philo->id);
	while (!all_threads_ready(table))
		;
	increase_int(&table->table_mutex, &table->threads_running);
	if (DEBUG == 1)
		printf(GREEN"[DEBUG] Philosopher %d started!"RESET"\n", philo->id);
	pthread_mutex_lock(&philo->first_fork->fork_mutex);
	write_status(philo, TAKEN_FORK);
	ft_usleep(msec_to_usec(philo->times->time_to_die));
	pthread_mutex_unlock(&philo->first_fork->fork_mutex);
	return (NULL);
}

void	*philo_routine(void *philosopher)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *) philosopher;
	table = (t_table *) philo->table;
	if (DEBUG == 1)
		printf(YELLOW"[DEBUG] Philosopher %d ready!"RESET"\n", philo->id);
	while (!all_threads_ready(table))
		;
	increase_int(&table->table_mutex, &table->threads_running);
	if (DEBUG == 1)
		printf(GREEN"[DEBUG] Philosopher %d started!"RESET"\n", philo->id);
	while (!all_threads_running(table))
		;
	while (!simulation_finished(table))
	{
		p_eat(philo);
		if (philo->is_full || simulation_finished(table))
			break ;
		p_sleep(philo);
		if (simulation_finished(table))
			break ;
		p_think(philo);
	}
	return (NULL);
}
