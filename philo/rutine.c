/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:41:04 by cgaratej          #+#    #+#             */
/*   Updated: 2024/09/23 18:04:17 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checke_deat(t_info *info)
{
	int	i;

	while (!info->dead)
	{
		i = 1;
		while (i <= info->num_philo)
		{
			printf("hola\n");
			pthread_mutex_lock(&info->m_eat);
			if (timestamp() - info->philo[i].last_eat >= info->time_die)
			{
				pthread_mutex_unlock(&info->m_eat);
				print(&info->philo[i], " died\n");
				return (1);
			}
			pthread_mutex_unlock(&info->m_eat);
			i++;
		}
		return (0);
	}
	return (0);
}

void	take_fork(t_philo *philo)
{

	pthread_mutex_lock(&philo->fork_l);
	print(philo, " has taken a fork\n");
	pthread_mutex_lock(philo->fork_r);
	print(philo, " has taken a fork\n");
}

void	eating(t_philo *philo)
{
	print(philo, " is eating\n");
	pthread_mutex_lock(&philo->info->m_eat);
	philo->last_eat = timestamp();
	philo->m_count++;
	pthread_mutex_unlock(&philo->info->m_eat);
	ft_usleep(philo->info->time_eat);
	pthread_mutex_unlock(&philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	print(philo, " is sleeping\n");
	ft_usleep(philo->info->time_sleep);
}

void	*philo_life(void *phi)
{
	t_philo		*philo;

	philo = (t_philo *)phi;
	if (philo->info->num_philo == 1)
	{
		pthread_mutex_lock(&philo->fork_l);
		print(philo, " has taken a fork\n");
		ft_usleep(philo->info->time_die);
		pthread_mutex_unlock(&philo->fork_l);
		print(philo, " died\n");
		return (NULL);
	}
	while (!philo->info->dead)
	{
		if (philo->id % 2 == 0 && !philo->m_count)
			ft_usleep(philo->info->time_eat);
		else
		{
			if (philo->id == philo->info->num_philo && !philo->last_eat)
				ft_usleep(philo->info->time_eat);
		}
		if (philo->info->num_philo % 2 != 0 && philo->m_count)
			ft_usleep(philo->info->time_eat);
		take_fork(philo);
		eating(philo);
	}
	return (NULL);
}