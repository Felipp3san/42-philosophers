/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:11:50 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/23 14:14:26 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	all_philos_full(t_table *table);
static t_bool	is_full(t_philo *philo);
static t_bool	is_dead(t_philo *philo);

void	verify(t_table *table, t_philo *philo)
{
	if (!is_full(philo) && is_dead(philo))
	{
		log_debug(RED, "Dead philosopher found, stopping threads...");
		set_bool(&table->table_mutex, &table->finished, TRUE);
		write_status(philo, DEAD);
	}
	else if (all_philos_full(table))
	{
		log_debug(GREEN, "All philos are full, stopping simulation...");
		set_bool(&table->table_mutex, &table->finished, TRUE);
	}
}

static t_bool	all_philos_full(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
	{
		if (!is_full(&table->philos[i]))
			return (FALSE);
	}
	return (TRUE);
}

static t_bool	is_full(t_philo *philo)
{
	return (get_bool(&philo->meal_mutex, &philo->is_full));
}

static t_bool	is_dead(t_philo *philo)
{
	t_ull	elapsed;

	elapsed = now_in_ms() - get_ull(&philo->meal_mutex, &philo->last_meal);
	if (elapsed > philo->times->time_to_die)
		return (TRUE);
	else
		return (FALSE);
}
