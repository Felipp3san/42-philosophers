/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:14:55 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/13 22:44:28 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo *philo, t_state state)
{
	t_table	*table;
	size_t	now;

	table = philo->table;
	now = now_in_ms();
	pthread_mutex_lock(&philo->write_mutex);
	if (state == TAKEN_FORK && !simulation_finished(table))
		printf(WHITE"%zu"RESET" %d has taken a fork\n", now, philo->id);
	else if (state == EATING && !simulation_finished(table))
		printf(WHITE"%zu"CYAN" %d is eating\n"RESET, now, philo->id);
	else if (state == THINKING && !simulation_finished(table))
		printf(WHITE"%zu"RESET" %d is thinking\n", now, philo->id);
	else if (state == SLEEPING && !simulation_finished(table))
		printf(WHITE"%ju"RESET" %d is sleeping\n", now, philo->id);
	else if (state == DEAD)
		printf(WHITE"%zu"RED" %d died\n"RESET, now, philo->id);
	pthread_mutex_unlock(&philo->write_mutex);
}
