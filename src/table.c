/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:04:54 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/13 13:46:19 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all_table(t_table *table, char *argv[])
{
	init_table(table, argv);
	if (init_table_mutexes(table) == MUTEX_ERROR)
		return (MUTEX_ERROR);
	return (SUCCESS);
}

void init_table(t_table *table, char *argv[])
{
	table->start_time = now_in_ms();
	table->n_philos = ft_atoi(argv[N_PHILOS]);
	table->time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	table->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	table->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (argv[MEALS_TO_EAT])
		table->meals_to_eat = ft_atoi(argv[MEALS_TO_EAT]);
	else
		table->meals_to_eat = -1;
	table->finished = false;
}

int	init_table_mutexes(t_table *table)
{
	int		status;

	status = pthread_mutex_init(&table->simulation_mutex, NULL);
	if (status != 0)
	{
		pthread_mutex_destroy(&table->simulation_mutex);
		return (MUTEX_ERROR);
	}
	return (SUCCESS);
}

void	destroy_table_mutexes(t_table *table)
{
	if (!table)
		return ;
	pthread_mutex_destroy(&table->simulation_mutex);
}

void	clean_table(t_table *table)
{
	destroy_table_mutexes(table);
}
