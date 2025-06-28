/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:23:52 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/28 12:32:11 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	res;

	mutex_handler(mutex, LOCK);
	res = *value;
	mutex_handler(mutex, UNLOCK);
	return (res);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	mutex_handler(mutex, LOCK);
	*dest = value;
	mutex_handler(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	res;

	mutex_handler(mutex, LOCK);
	res = *value;
	mutex_handler(mutex, UNLOCK);
	return (res);
}

bool	is_simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
