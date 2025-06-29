/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:56:42 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/29 13:37:39 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->is_full))
		return (false);
	elapsed = ft_gettime(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table *table;

	table = (t_table *)data;
	while (!threads_running(&table->table_mutex, &table->threads_running_nbr, table->philo_nbr))
		;
	while (!is_simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !is_simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}