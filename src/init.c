/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:14:18 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/23 13:28:20 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_all_philos(t_table *table);
static int	init_all_forks(t_table *table);
static int	init_all_table(t_table *table, char *argv[]);

void	init_data(t_table *table, char *argv[])
{
	if (init_all_table(table, argv) != SUCCESS)
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

static int	init_all_philos(t_table *table)
{
	if (init_philosophers(table) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (init_philosophers_mutexes(table) == MUTEX_ERROR)
	{
		free(table->philos);
		return (MUTEX_ERROR);
	}
	return (SUCCESS);
}

static int	init_all_forks(t_table *table)
{
	if (init_forks(table) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (init_forks_mutexes(table) == MUTEX_ERROR)
	{
		free(table->forks);
		return (MUTEX_ERROR);
	}
	return (SUCCESS);
}

static int	init_all_table(t_table *table, char *argv[])
{
	init_table(table, argv);
	if (init_table_mutexes(table) == MUTEX_ERROR)
		return (MUTEX_ERROR);
	return (SUCCESS);
}
