/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:04:54 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/26 18:20:57 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "types.h"

void	init_table(t_table *table, char *argv[])
{
	table->n_philos = ft_atoi(argv[N_PHILOS]);
	table->thread_failure = FALSE;
	table->times.start_time = now_in_ms();
	table->times.time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	table->times.time_to_die = ft_atoi(argv[TIME_TO_DIE]); table->times.time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (argv[MEALS_TO_EAT])
		table->meals_to_eat = ft_atoi(argv[MEALS_TO_EAT]);
	else
		table->meals_to_eat = -1;
	table->finished = FALSE;
}

int	init_table_mutexes(t_table *table)
{
	int	status;

	status = pthread_mutex_init(&table->threads_ready, NULL);
	if (status != 0)
		return (MUTEX_ERROR);
	status = pthread_mutex_init(&table->table_mutex, NULL);
	if (status != 0)
	{
		pthread_mutex_destroy(&table->threads_ready);
		return (MUTEX_ERROR);
	}
	status = pthread_mutex_init(&table->write_mutex, NULL);
	if (status != 0)
	{
		pthread_mutex_destroy(&table->threads_ready);
		pthread_mutex_destroy(&table->table_mutex);
		return (MUTEX_ERROR);
	}
	return (SUCCESS);
}

void	destroy_table_mutexes(t_table *table)
{
	if (!table)
		return ;
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->threads_ready);
	pthread_mutex_destroy(&table->write_mutex);
}

void	clean_table(t_table *table)
{
	destroy_table_mutexes(table);
}
