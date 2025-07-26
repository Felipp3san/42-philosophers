/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:36:32 by fde-alme          #+#    #+#             */
/*   Updated: 2025/07/23 13:35:48 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_params(char *argv[])
{
	if (!is_valid_number(argv[1]) || ft_atoi(argv[1]) <= 0)
		exit_error("Invalid number of philosophers");
	if (!is_valid_number(argv[2]) || ft_atoi(argv[2]) <= 0)
		exit_error("Invalid time to die");
	if (!is_valid_number(argv[3]) || ft_atoi(argv[3]) <= 0)
		exit_error("Invalid time to eat");
	if (!is_valid_number(argv[4]) || ft_atoi(argv[4]) <= 0)
		exit_error("Invalid time to sleep");
	if (argv[5])
	{
		if (!is_valid_number(argv[5]) || ft_atoi(argv[5]) <= 0)
			exit_error("Invalid number of meals");
	}
}

void	free_table(t_table *table)
{
	clean_table(table);
	clean_forks(table);
	clean_philosophers(table);
}

void	exit_error(const char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

/* arg must be and int, an ID for example... */
void	log_debug(t_table *table, const char *color, const char *msg, int *id)
{
	if (DEBUG != 1)
		return ;
	pthread_mutex_lock(&table->write_mutex);
	printf("%s[DEBUG] ", color);
	printf("%s", msg);
	if (id != NULL)
		printf(" [ID: %d]", *id);
	printf(RESET"\n");
	pthread_mutex_unlock(&table->write_mutex);
}
