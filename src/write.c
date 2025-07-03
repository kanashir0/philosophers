/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 13:07:14 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/02 21:01:24 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	write_status_debug(t_philo_status status, t_philo *philo, long elapsed)
{
	if (status == TAKE_FIRST_FORK && !is_simulation_finished(philo->table))
		printf("%-6ld %d has taken the 1st fork"
			"\t\t\tn: %d\n", elapsed, philo->id, philo->first_fork->fork_id);
	else if (status == TAKE_SECOND_FORK
		&& !is_simulation_finished(philo->table))
		printf("%-6ld %d has taken the 2nd fork"
			"\t\t\tn: %d\n", elapsed, philo->id, philo->second_fork->fork_id);
	else if (status == EATING && !is_simulation_finished(philo->table))
		printf("%-6ld %d is eating"
			"\t\t\t %ld\n", elapsed, philo->id, philo->meals_count);
	else if (status == SLEEPING && !is_simulation_finished(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !is_simulation_finished(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%-6ld %d died\n", elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = ft_gettime(MILLISECOND) - philo->table->start_simulation;
	if (philo->is_full)
		return ;
	mutex_handler(&philo->table->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !is_simulation_finished(philo->table))
			printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING && !is_simulation_finished(philo->table))
			printf("%-6ld %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING && !is_simulation_finished(philo->table))
			printf("%-6ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING && !is_simulation_finished(philo->table))
			printf("%-6ld %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf("%-6ld %d died\n", elapsed, philo->id);
	}
	mutex_handler(&philo->table->write_mutex, UNLOCK);
}
