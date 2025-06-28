/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:13:47 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/28 13:00:22 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);
	while (!is_simulation_finished(philo->table))
	{
		if (philo->is_full)
			break ;
		eat(philo);
		
		thinking(philo);
	}
}

void	dinner_start(t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		;
	else
	{
		while (i++ < table->philo_nbr)
			thread_handler(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	table->start_simulation = ft_gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->threads_ready, true);
	i = 0;
	while (i++ < table->philo_nbr)
		thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN);
	
}
