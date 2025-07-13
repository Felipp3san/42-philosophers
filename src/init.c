/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:14:18 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/13 13:49:00 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_table *table, char *argv[])
{
	if (init_all_table(table, argv)!= SUCCESS)
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

