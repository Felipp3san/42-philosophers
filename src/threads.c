/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:30:30 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/23 13:30:52 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_table	*table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
		pthread_join(table->philos[i].thread, NULL);
	pthread_join(table->death_monitor, NULL);
}

// TODO: Lone philosopher
void	init_threads(t_table *table)
{
	t_philo	*philo;
	int		status;
	int		i;

	i = -1;
	while (++i < table->n_philos)
	{
		philo = &table->philos[i];
		status = pthread_create(&philo->thread, NULL,
				philo_routine, (void *) philo);
		if (status != 0)
		{
			free_table(table);
			exit_error("Failed to create thread");
		}
	}
	table->times.start_time = now_in_ms();
	set_bool(&table->table_mutex, &table->threads_ready, TRUE);
}
