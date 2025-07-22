/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:41:22 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/22 18:59:55 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_int(t_mutex *mutex, int *dest, int value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

void	increase_int(t_mutex *mutex, int *dest)
{
	pthread_mutex_lock(mutex);
	(*dest)++;
	pthread_mutex_unlock(mutex);
}

void	set_ull(t_mutex *mutex, t_ull *dest, t_ull value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

void	set_bool(t_mutex *mutex, t_bool *dest, t_bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}
