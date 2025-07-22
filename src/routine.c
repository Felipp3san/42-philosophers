/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:50:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/22 19:52:46 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *philosopher)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *) philosopher;
	table = (t_table *) philo->table;
	while (!all_threads_ready(table))
		ft_usleep(100);
	increase_int(&table->table_mutex, &table->threads_running);
	while (!all_threads_running(table))
		;
	while (!simulation_finished(table))
	{
		p_eat(philo);
		if (simulation_finished(table))
			break ;
		p_sleep(philo);
		if (simulation_finished(table))
			break ;
		p_think(philo);
	}
	return (NULL);
}

void	*philo_routine_debug(void *philosopher)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *) philosopher;
	table = (t_table *) philo->table;
	printf(YELLOW"[DEBUG] Philosopher %d ready!"RESET"\n", philo->id);
	while (!all_threads_ready(table))
		ft_usleep(100);
	increase_int(&table->table_mutex, &table->threads_running);
	while (!all_threads_running(table))
		;
	printf(GREEN"[DEBUG] Philosopher %d started!"RESET"\n", philo->id);
	while (!simulation_finished(table))
	{
		p_eat(philo);
		if (simulation_finished(table))
			break ;
		p_sleep(philo);
		if (simulation_finished(table))
			break ;
		p_think(philo);
	}
	return (NULL);
}
