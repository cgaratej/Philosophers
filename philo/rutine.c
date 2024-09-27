/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:41:04 by cgaratej          #+#    #+#             */
/*   Updated: 2024/09/27 15:19:56 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checke_deat(t_info *info)
{
	int	i;

	while (!info->dead)
	{
		i = 1;
		while (i < info->num_philo)
		{
			//pthread_mutex_lock(&info->m_eat);
			mutex_handle(&info->m_eat, LOCK, i);
			if (timestamp() - info->philo[i].last_eat >= info->time_die)
			{
				pthread_mutex_unlock(&info->m_eat);
				print(&info->philo[i], " died\n");
				return (1);
			}
			//pthread_mutex_unlock(&info->m_eat);
			mutex_handle(&info->m_eat, UNLOCK, i);
			i++;
		}
	}
	return (0);
}

void	take_fork(t_philo *philo)
{
	//ft_usleep(1);
	if (philo->id % 2 == 0)
	{	
		//pthread_mutex_lock(&philo->fork_l);
		mutex_handle(&philo->fork_l, LOCK, philo->id);
		print(philo, " has taken a fork\n");
		//pthread_mutex_lock(philo->fork_r);
		mutex_handle(philo->fork_r, LOCK, philo->id);
		print(philo, " has taken a fork\n");
	}
	else
	{
		//pthread_mutex_lock(philo->fork_r);
		mutex_handle(philo->fork_r, LOCK, philo->id);
		print(philo, " has taken a fork\n");
		//pthread_mutex_lock(&philo->fork_l);
		mutex_handle(&philo->fork_l, LOCK, philo->id);
		print(philo, " has taken a fork\n");
	}
}

void	eating(t_philo *philo)
{
	print(philo, " is eating\n");
	//pthread_mutex_lock(&philo->info->m_eat);
	mutex_handle(&philo->info->m_eat, LOCK, philo->id);
	philo->last_eat = timestamp();
	philo->m_count++;
	//pthread_mutex_unlock(&philo->info->m_eat);
	mutex_handle(&philo->info->m_eat, UNLOCK, philo->id);
	ft_usleep(philo->info->time_eat);
	/*pthread_mutex_unlock(&philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);*/
	mutex_handle(&philo->fork_l, UNLOCK, philo->id);
	mutex_handle(philo->fork_r, UNLOCK, philo->id);
	print(philo, " is sleeping\n");
	ft_usleep(philo->info->time_sleep);
	if (philo->info->num_philo % 2 == 0)
		print(philo, " is thinking\n");
}

void	*philo_life(void *phi)
{
	t_philo		*philo;

	philo = (t_philo *)phi;
	if (philo->info->num_philo == 1)
	{
		//pthread_mutex_lock(&philo->fork_l);
		mutex_handle(&philo->fork_l, LOCK, philo->id);
		print(philo, " has taken a fork\n");
		ft_usleep(philo->info->time_die);
		//pthread_mutex_unlock(&philo->fork_l);
		mutex_handle(&philo->fork_l, UNLOCK, philo->id);
		print(philo, " died\n");
		philo->info->dead = 1;
		return (NULL);
	}
	while (!philo->info->dead)
	{
		if (philo->id % 2 == 0 && !philo->m_count)
		{
			print(philo, " is thinking\n");
			ft_usleep(philo->info->time_eat);
		}
		else
		{
			if (philo->id == philo->info->num_philo && !philo->m_count)
			{
				print(philo, " is thinking\n");
				ft_usleep(philo->info->time_eat);
			}
		}
		if (philo->info->num_philo % 2 != 0 && philo->m_count)
		{
			print(philo, " is thinking\n");
			ft_usleep(philo->info->time_eat);
		}
		take_fork(philo);
		eating(philo);
		/*pthread_mutex_lock(&philo->info->m_eat);
		if (philo->info->num_eat == philo->m_count)
		{
			print(philo, " finish\n");
			philo->info->dead = 2;
			pthread_mutex_unlock(&philo->info->m_eat);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->m_eat);*/
	}
	return (NULL);
}
