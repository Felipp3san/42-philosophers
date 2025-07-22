/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:00:31 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/22 20:00:33 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	is_full(t_philo *philo);

void	*meal_monitor(void *data)
{
	t_table	*table;
	t_philo	*philo;
	int		i;

	table = (t_table *) data;
	while (!all_threads_running(table))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->n_philos && !simulation_finished(table))
		{
			philo = (t_philo *) &table->philos[i];
			if (is_full(philo))
				set_bool(&table->table_mutex, &table->finished, TRUE);
		}
	}
	return (NULL);
}

void	*meal_monitor_debug(void *data)
{
	t_table	*table;
	t_philo	*philo;
	int		i;

	table = (t_table *) data;
	printf(YELLOW"[DEBUG] Meal monitor started!"RESET"\n");
	while (!all_threads_running(table))
		;
	printf(GREEN"[DEBUG] Meal monitor started!"RESET"\n");
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->n_philos && !simulation_finished(table))
		{
			philo = (t_philo *) &table->philos[i];
			if (is_full(philo))
			{
				printf(GREEN"[DEBUG] 🐷🐷 Full philosopher found, stopping threads... 🐷🐷 "RESET
					"[Philosopher ID: %d - Meals Eaten: %d]\n", philo->id, philo->meals_eaten);
				set_bool(&table->table_mutex, &table->finished, TRUE);
			}
		}
	}
	return (NULL);
}

static t_bool	is_full(t_philo *philo)
{
	int	meals_eaten;

	meals_eaten = get_int(&philo->meal_mutex, &philo->meals_eaten);
	if (meals_eaten == philo->table->meals_to_eat)
		return (TRUE);
	else
		return (FALSE);
}
