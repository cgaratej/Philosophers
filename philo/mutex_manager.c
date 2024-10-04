/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:06:54 by cgaratej          #+#    #+#             */
/*   Updated: 2024/10/04 19:08:33 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	mutex_error_check(int status)
{
	if (status == INIT)
		return (printf("Problem initializing the mutex.\n"), 1);
	if (status == LOCK)
		return (printf("Problem locking the mutex.\n"), 1);
	if (status == UNLOCK)
		return (printf("Problem unlocking the mutex.\n"), 1);
	if (status == DESTROY)
		return (printf("Problem destroying the mutex.\n"), 1);
	return (0);
}

int	mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			return (mutex_error_check(INIT));
	}
	else if (opcode == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			return (mutex_error_check(LOCK));
	}
	else if (opcode == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			return (mutex_error_check(UNLOCK));
	}
	else if (opcode == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			return (mutex_error_check(DESTROY));
	}
	return (0);
}
