/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:05:46 by cgaratej          #+#    #+#             */
/*   Updated: 2024/10/21 12:29:16 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_philo(t_philo *philo)
{
	mutex_handle(&philo->fork_l, LOCK);
	print(philo, " has taken a fork\n", 0);
	ft_usleep(philo->info->time_die, philo->info);
	mutex_handle(&philo->fork_l, UNLOCK);
}

static void	philo_finish(t_philo *philo)
{
	mutex_handle(&philo->info->m_stop, LOCK);
	if (++philo->info->philo_eat == philo->info->num_philo)
		is_dead(philo->info, 2);
	mutex_handle(&philo->info->m_stop, UNLOCK);
}

void	*philo_life(void *phi)
{
	t_philo		*philo;

	philo = (t_philo *)phi;
	if (philo->info->num_philo == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while (!is_dead(philo->info, 0))
	{
		synchronized(philo);
		take_fork(philo);
		eating(philo);
		if (philo->m_count == philo->info->num_eat)
		{
			philo_finish(philo);
			return (NULL);
		}
	}
	return (NULL);
}
