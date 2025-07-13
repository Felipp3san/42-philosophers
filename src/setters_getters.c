/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:45:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/13 20:51:18 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Thread safe setters & getters */

void	set_bool(t_mutex *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(t_mutex *mutex, bool *target)
{
	bool	value;

	pthread_mutex_lock(mutex);
	value = *target;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	set_size_t(t_mutex *mutex, size_t *dest, size_t value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

size_t	get_size_t(t_mutex *mutex, size_t *target)
{
	size_t	value;

	pthread_mutex_lock(mutex);
	value = *target;
	pthread_mutex_unlock(mutex);
	return (value);
}

bool	simulation_finished(t_table *table)
{
	return get_bool(&table->simulation_mutex, &table->finished);
}
