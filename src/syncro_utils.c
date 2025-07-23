/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:50:18 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/23 12:58:16 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	all_threads_ready(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->threads_ready));
}

t_bool	all_threads_running(t_table *table)
{
	int	threads_running;

	threads_running = get_int(&table->table_mutex, &table->threads_running);
	if (table->n_philos == threads_running)
		return (TRUE);
	return (FALSE);
}
