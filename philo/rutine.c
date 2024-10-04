/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:41:04 by cgaratej          #+#    #+#             */
/*   Updated: 2024/10/04 18:55:16 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *info_void)
{
	t_info	*info;
	int		i;

	info = (t_info *)info_void;
	while (!is_dead(info, 0))
	{
		mutex_handle(&info->m_eat, LOCK);
		mutex_handle(&info->m_stop, LOCK);
		i = 0;
		while (i < info->num_philo && !is_dead(info, 0))
		{
			if (timestamp() - info->philo[i].last_eat >= (long)(info->time_die))
			{
				is_dead(info, 1);
				print(&info->philo[i], " died\n", 1);
			}
			i++;
		}
		mutex_handle(&info->m_eat, UNLOCK);
		mutex_handle(&info->m_stop, UNLOCK);
		usleep(250);
	}
	return (NULL);
}

int	is_dead(t_info *info, int nb)
{
	mutex_handle(&info->dead, LOCK);
	if (nb)
		info->stop = 1;
	if (info->stop)
	{
		mutex_handle(&info->dead, UNLOCK);
		return (1);
	}
	mutex_handle(&info->dead, UNLOCK);
	return (0);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		mutex_handle(&philo->fork_l, LOCK);
		print(philo, " has taken a fork\n", 0);
		mutex_handle(philo->fork_r, LOCK);
		print(philo, " has taken a fork\n", 0);
	}
	else
	{
		mutex_handle(philo->fork_r, LOCK);
		print(philo, " has taken a fork\n", 0);
		mutex_handle(&philo->fork_l, LOCK);
		print(philo, " has taken a fork\n", 0);
	}
}

void	eating(t_philo *philo)
{
	print(philo, " is eating\n", 0);
	mutex_handle(&philo->info->m_eat, LOCK);
	philo->last_eat = timestamp();
	philo->m_count++;
	mutex_handle(&philo->info->m_eat, UNLOCK);
	ft_usleep(philo->info->time_eat, philo->info);
	mutex_handle(&philo->fork_l, UNLOCK);
	mutex_handle(philo->fork_r, UNLOCK);
	print(philo, " is sleeping\n", 0);
	ft_usleep(philo->info->time_sleep, philo->info);
	if (philo->info->num_philo % 2 == 0)
		print(philo, " is thinking\n", 0);
}

void	one_philo(t_philo *philo)
{
	mutex_handle(&philo->fork_l, LOCK);
	print(philo, " has taken a fork\n", 0);
	ft_usleep(philo->info->time_die, philo->info);
	mutex_handle(&philo->fork_l, UNLOCK);
}

void	synchronized(t_philo *philo)
{
	if (philo->id % 2 == 0 && !philo->m_count)
	{
		print(philo, " is thinking\n", 0);
		ft_usleep(philo->info->time_eat, philo->info);
	}
	else
	{
		if (philo->id == philo->info->num_philo && !philo->m_count)
		{
			print(philo, " is thinking\n", 0);
			ft_usleep(philo->info->time_eat * 2, philo->info);
		}
	}
	if (philo->info->num_philo % 2 != 0 && philo->m_count)
	{
		print(philo, " is thinking\n", 0);
		ft_usleep(philo->info->time_eat, philo->info);
	}
}

void	philo_finish(t_philo *philo)
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
