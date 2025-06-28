/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:59:47 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/28 12:23:00 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(position + 1) % philo_nbr];
	philo->second_fork = &forks[position];
	if (philo->id % 2)
	{
		philo->first_fork = &forks[position];
		philo->second_fork = &forks[(position + 1) % philo_nbr];
	}

}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i++ < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->is_full = false;
		philo->meals_count = 0;
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
}

void	init_data(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->threads_ready = false;
	table->philos = ft_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = ft_malloc(sizeof(t_fork) * table->philo_nbr);
	mutex_handler(&table->table_mutex, INIT);
	while (i++ < table->philo_nbr)
	{
		mutex_handler(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);

}