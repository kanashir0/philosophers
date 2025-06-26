/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:42:20 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/06/25 21:19:23 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		// data_init(&table);
		// dinner_start(&table);
		// clean_all(&table);
	}
	else
	{
		error_exit("Wrong input:\n"
				"Correct is ./philo 5 800 200 200 [5]");
	}
}