/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:05:46 by cgaratej          #+#    #+#             */
/*   Updated: 2024/10/22 16:11:17 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_philo(t_philo *philo)
{
	mutex_handle(&philo->fork_l, LOCK);
	print(philo, " has taken a fork 🍴\n", 0);
	ft_usleep(philo->info->time_die, philo->info);
	mutex_handle(&philo->fork_l, UNLOCK);
}

void	check_finish(t_info *info)
{
	int	i;

	i = -1;
	info->philo_eat = 0;
	while (++i < info->num_philo && !is_dead(info, 0))
	{
		if (info->philo[i].m_count == info->num_eat)
			info->philo_eat++;
	}
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
			return (NULL);
	}
	return (NULL);
}
