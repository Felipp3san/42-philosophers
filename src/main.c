/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:07:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/23 13:35:26 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc < ARG_MIN_COUNT || argc > ARG_MAX_COUNT)
		exit_error("Invalid number of parameters");
	check_params(argv);
	init_data(&table, argv);
	init_monitor_thread(&table);
	init_philos_threads(&table);
	join_threads(&table);
	free_table(&table);
	return (EXIT_SUCCESS);
}
