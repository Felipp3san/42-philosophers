/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:55:37 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/23 14:15:06 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		*monitor(void	*data);

void	init_monitor(t_table *table)
{
	int	status;

	status = pthread_create(&table->death_monitor,
			NULL, monitor, (void *) table);
	if (status != 0)
	{
		free_table(table);
		exit_error("Failed to create death monitor thread");
	}
}

static void	*monitor(void *data)
{
	t_table	*table;
	t_philo	*philo;
	int		i;

	table = (t_table *) data;
	log_debug(YELLOW, "Monitor ready!");
	while (!all_threads_running(table))
		;
	log_debug(GREEN, "Monitor started!");
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->n_philos && !simulation_finished(table))
		{
			philo = (t_philo *) &table->philos[i];
			verify(table, philo);
		}
	}
	return (NULL);
}
