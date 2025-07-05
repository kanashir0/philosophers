/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyasuhir <gyasuhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:02:22 by gyasuhir          #+#    #+#             */
/*   Updated: 2025/07/05 15:01:43 by gyasuhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*ft_malloc(size_t bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
		error_exit("Error with malloc!\n");
	return (ptr);
}

static void	mutex_error_handler(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK
			|| opcode == UNLOCK || opcode == DESTROY))
		error_exit("The value specified by mutex is invalid.\n");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid.\n");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if the thread"
			"blocked waiting for mutex.\n");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex.\n");
	else if (status == ENOMEM)
		error_exit("The process cannot allocate enough"
			"memory to create another mutex.\n");
	else if (status == EBUSY)
		error_exit("Mutex is locked.\n");
}

void	mutex_handler(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		mutex_error_handler(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		mutex_error_handler(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		mutex_error_handler(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		mutex_error_handler(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex!\n");
}

static void	thread_error_handler(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resources to create another thread.\n");
	else if (status == EPERM)
		error_exit("The caller does not have appropriate permissions.\n");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid.\n");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("The value specified by thread is not joinable.\n");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to that "
			"specified by the given thread ID, thread.\n");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of"
			"thread specifies the callind thread.");
}

void	thread_handler(pthread_t *thread, void *(*func)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		thread_error_handler(pthread_create(thread, NULL, func, data), opcode);
	else if (opcode == JOIN)
		thread_error_handler(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		thread_error_handler(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread_handle:"
			"use <CREATE> <JOIN> <DETACH>");
}
