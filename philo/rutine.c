/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:41:04 by cgaratej          #+#    #+#             */
/*   Updated: 2024/10/22 16:11:05 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philo_death(t_info *info, int i)
{
	if (timestamp() - info->philo[i].last_eat >= (long)(info->time_die))
	{
		check_finish(info);
		if (info->philo_eat == info->num_philo && info->num_philo != 1)
			is_dead(info, 2);
		else
		{
			is_dead(info, 1);
			print(&info->philo[i], " died 😵\n", 1);
		}
	}
}

void	*check_death(void *info_void)
{
	t_info	*info;
	int		i;

	info = (t_info *)info_void;
	while (!is_dead(info, 0))
	{
		mutex_handle(&info->m_eat, LOCK);
		mutex_handle(&info->m_stop, LOCK);
		i = -1;
		while (++i < info->num_philo && !is_dead(info, 0))
		{
			check_philo_death(info, i);
		}
		mutex_handle(&info->m_eat, UNLOCK);
		mutex_handle(&info->m_stop, UNLOCK);
		usleep(250);
	}
	return (NULL);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		mutex_handle(&philo->fork_l, LOCK);
		print(philo, " has taken a fork 🍴\n", 0);
		mutex_handle(philo->fork_r, LOCK);
		print(philo, " has taken a fork 🍴\n", 0);
	}
	else
	{
		mutex_handle(philo->fork_r, LOCK);
		print(philo, " has taken a fork 🍴\n", 0);
		mutex_handle(&philo->fork_l, LOCK);
		print(philo, " has taken a fork 🍴\n", 0);
	}
}

void	eating(t_philo *philo)
{
	print(philo, " is eating 🍝\n", 0);
	mutex_handle(&philo->info->m_eat, LOCK);
	philo->last_eat = timestamp();
	philo->m_count++;
	mutex_handle(&philo->info->m_eat, UNLOCK);
	ft_usleep(philo->info->time_eat, philo->info);
	mutex_handle(&philo->fork_l, UNLOCK);
	mutex_handle(philo->fork_r, UNLOCK);
	print(philo, " is sleeping 😴\n", 0);
	ft_usleep(philo->info->time_sleep, philo->info);
	if (philo->info->num_philo % 2 == 0)
		print(philo, " is thinking 🤔\n", 0);
}

void	synchronized(t_philo *philo)
{
	if (philo->id % 2 == 0 && !philo->m_count)
	{
		print(philo, " is thinking 🤔\n", 0);
		ft_usleep(philo->info->time_eat, philo->info);
	}
	else
	{
		if (philo->id == philo->info->num_philo && !philo->m_count)
		{
			print(philo, " is thinking 🤔\n", 0);
			ft_usleep(philo->info->time_eat * 2, philo->info);
		}
	}
	if (philo->info->num_philo % 2 != 0 && philo->m_count)
	{
		print(philo, " is thinking 🤔\n", 0);
		ft_usleep(philo->info->time_eat, philo->info);
	}
}
