/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:16:48 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/13 22:23:15 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*death_monitor(void	*table);
static bool	is_dead(t_philo *philo);

void	init_monitor(pthread_t *monitor, t_table *table)
{
	int	status;

	status = pthread_create(monitor, NULL, death_monitor, (void *) table);
	if (status != 0)
	{
		free_table(table);
		exit_error("Failed to create monitor thread");
	}
}

static bool	is_dead(t_philo *philo)
{
	size_t	elapsed;

	elapsed = now_in_ms() - get_size_t(&philo->meal_mutex, &philo->last_meal_time);
	if (elapsed > philo->table->time_to_die)
		return (true);
	else
		return (false);
}

// TODO: Wait for all threads to start
static void	*death_monitor(void	*data)
{
	t_table	*table;
	t_philo	*philo;
	ssize_t	i;

	// Wait here
	//
	// ________

	table = (t_table *) data;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->n_philos && !simulation_finished(table))
		{
			philo = (t_philo *) &table->philos[i];
			if (is_dead(philo))
			{
				set_bool(&table->simulation_mutex, &table->finished, true);
				write_status(philo, DEAD);
			}
		}
	}
	return (NULL);
}
