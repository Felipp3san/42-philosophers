/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:30:30 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/26 18:29:43 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_table	*table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
		pthread_join(table->philos[i].thread, NULL);
	pthread_join(table->monitor, NULL);
}

void	init_philos_threads(t_table *table)
{
	int		status;
	int		i;

	i = -1;
	pthread_mutex_lock(&table->threads_ready);
	while (++i < table->n_philos)
	{
		if (table->n_philos == 1)
			status = pthread_create(&table->philos[i].thread, NULL,
					lone_philo_routine, (void *) &table->philos[i].thread);
		else
			status = pthread_create(&table->philos[i].thread, NULL,
					philo_routine, (void *) &table->philos[i].thread);
		if (status != 0)
		{
			set_bool(&table->table_mutex, &table->thread_failure, TRUE);
			pthread_mutex_unlock(&table->threads_ready);
			while (--i >= 0)
				pthread_join(table->philos[i].thread, NULL);
			free_table(table);
			exit_error("Failed to create thread");
		}
	}
	pthread_mutex_unlock(&table->threads_ready);
}

// TODO: If monitor fails, it should join all philo threads.
void	init_monitor_thread(t_table *table)
{
	int	status;

	status = pthread_create(&table->monitor,
			NULL, monitor, (void *) table);
	if (status != 0)
	{
		free_table(table);
		exit_error("Failed to create monitor thread");
	}
}
