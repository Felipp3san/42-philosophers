/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:03:22 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/13 14:15:49 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo);

int	init_all_philos(t_table *table)
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

int init_philosophers(t_table *table)
{
	ssize_t	i;
	t_philo	*philo;

	table->philos = (t_philo *) malloc(sizeof(t_philo) * table->n_philos);
	if (!table->philos)
		return (MALLOC_ERROR);
	i = -1;
	while (++i < table->n_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->last_meal_time = table->start_time;
		philo->meals_eaten = 0;
		philo->table = table;
		assign_forks(philo);
	}
	return (SUCCESS);
}

int init_philosophers_mutexes(t_table *table)
{
	ssize_t	i;
	int		status;

	i = -1;
	while (++i < table->n_philos)
	{
		status = pthread_mutex_init(&table->philos[i].meal_mutex, NULL);
		if (status != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->philos[i].meal_mutex);
			return (MUTEX_ERROR);
		}
		status = pthread_mutex_init(&table->philos[i].write_mutex, NULL);
		if (status != 0)
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&table->philos[i].meal_mutex);
				pthread_mutex_destroy(&table->philos[i].write_mutex);
			}
			return (MUTEX_ERROR);
		}
	}
	return (SUCCESS);
}

void	destroy_philosophers_mutexes(t_table *table)
{
	ssize_t	i;

	if (!table)
		return ;
	i = -1;
	while (++i < table->n_philos)
	{
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		pthread_mutex_destroy(&table->philos[i].write_mutex);
	}
}

void	clean_philosophers(t_table *table)
{
	if (table->philos)
	{
		destroy_philosophers_mutexes(table);
		free(table->philos);
		table->philos = NULL;
	}
}

static void	assign_forks(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &table->forks[philo->id - 1];
		philo->second_fork = &table->forks[philo->id % table->n_philos];
	}
	else
	{
		philo->first_fork = &table->forks[philo->id % table->n_philos];
		philo->second_fork = &table->forks[philo->id - 1];
	}
}
