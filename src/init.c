/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:14:18 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/23 11:56:20 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_table *table, char *argv[])
{
	if (init_all_table(table, argv)!= SUCCESS)
		exit_error("Failed to init table");
	if (init_all_forks(table) != SUCCESS)
	{
		clean_table(table);
		exit_error("Failed to init forks");
	}
	if (init_all_philos(table) != SUCCESS)
	{
		clean_table(table);
		clean_forks(table);
		exit_error("Failed to init philosophers");
	}
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
		status = pthread_create(&philo->thread, NULL, philo_routine, (void *) philo);
		if (status != 0)
		{
			free_table(table);
			exit_error("Failed to create thread");
		}
	}
	table->times.start_time = now_in_ms();
	set_bool(&table->table_mutex, &table->threads_ready, TRUE);
}

