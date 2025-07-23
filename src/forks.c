/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:59:47 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/23 13:26:47 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_table *table)
{
	int	i;

	table->forks = (t_fork *) malloc(sizeof(t_fork) * table->n_philos);
	if (!table->forks)
		return (MALLOC_ERROR);
	i = -1;
	while (++i < table->n_philos)
		table->forks[i].id = i;
	return (SUCCESS);
}

int	init_forks_mutexes(t_table *table)
{
	int	i;
	int	status;

	i = -1;
	while (++i < table->n_philos)
	{
		status = pthread_mutex_init(&table->forks[i].fork_mutex, NULL);
		if (status != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i].fork_mutex);
			return (MUTEX_ERROR);
		}
	}
	return (SUCCESS);
}

void	destroy_forks_mutexes(t_table *table)
{
	int	i;

	if (!table)
		return ;
	i = -1;
	while (++i < table->n_philos)
		pthread_mutex_destroy(&table->forks[i].fork_mutex);
}

void	clean_forks(t_table *table)
{
	if (table->forks)
	{
		destroy_forks_mutexes(table);
		free(table->forks);
		table->forks = NULL;
	}
}
