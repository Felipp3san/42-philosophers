/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:38:43 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/26 18:19:42 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Thread safe getters */

int	get_int(t_mutex *mutex, int *target)
{
	int	value;

	pthread_mutex_lock(mutex);
	value = *target;
	pthread_mutex_unlock(mutex);
	return (value);
}

t_ull	get_ull(t_mutex *mutex, t_ull *target)
{
	t_ull	value;

	pthread_mutex_lock(mutex);
	value = *target;
	pthread_mutex_unlock(mutex);
	return (value);
}

t_bool	get_bool(t_mutex *mutex, t_bool *target)
{
	t_bool	value;

	pthread_mutex_lock(mutex);
	value = *target;
	pthread_mutex_unlock(mutex);
	return (value);
}

t_bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->finished));
}

t_bool	thread_creation_failed(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->thread_failure));
}
