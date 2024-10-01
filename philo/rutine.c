/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:41:04 by cgaratej          #+#    #+#             */
/*   Updated: 2024/10/01 15:04:50 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	ft_usleep(philo->info->time_die + 1);
	mutex_handle(&philo->info->m_eat, LOCK);
	mutex_handle(&philo->info->m_stop, LOCK);
	if (!is_dead(philo, 0) && timestamp() - \
			philo->last_eat >= (long)(philo->info->time_die))
	{
		mutex_handle(&philo->info->m_eat, UNLOCK);
		mutex_handle(&philo->info->m_stop, UNLOCK);
		print(philo, " died\n");
		is_dead(philo, 1);
	}
	//mutex_handle(&philo->info->m_eat, UNLOCK);
	//mutex_handle(&philo->info->m_stop, UNLOCK);
	return (NULL);
}

int	is_dead(t_philo *philo, int nb)
{
	mutex_handle(&philo->info->dead, LOCK);
	if (nb)
		philo->info->stop = 1;
	if (philo->info->stop)
	{
		mutex_handle(&philo->info->dead, UNLOCK);
		return (1);
	}
	mutex_handle(&philo->info->dead, UNLOCK);
	return (0);
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{	
		mutex_handle(&philo->fork_l, LOCK);
		print(philo, " has taken a fork\n");
		mutex_handle(philo->fork_r, LOCK);
		print(philo, " has taken a fork\n");
	}
	else
	{
		mutex_handle(philo->fork_r, LOCK);
		print(philo, " has taken a fork\n");
		mutex_handle(&philo->fork_l, LOCK);
		print(philo, " has taken a fork\n");
	}
}

void	eating(t_philo *philo)
{
	print(philo, " is eating\n");
	mutex_handle(&philo->info->m_eat, LOCK);
	philo->last_eat = timestamp();
	philo->m_count++;
	mutex_handle(&philo->info->m_eat, UNLOCK);
	ft_usleep(philo->info->time_eat);
	mutex_handle(&philo->fork_l, UNLOCK);
	mutex_handle(philo->fork_r, UNLOCK);
	print(philo, " is sleeping\n");
	ft_usleep(philo->info->time_sleep);
	if (philo->info->num_philo % 2 == 0)
		print(philo, " is thinking\n");
}

void	one_philo(t_philo *philo)
{
	mutex_handle(&philo->fork_l, LOCK);
	print(philo, " has taken a fork\n");
	ft_usleep(philo->info->time_die);
	mutex_handle(&philo->fork_l, UNLOCK);
	print(philo, " died\n");
}

void	synchronized(t_philo *philo)
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
			ft_usleep(philo->info->time_eat * 2);
		}
	}
	if (philo->info->num_philo % 2 != 0 && philo->m_count)
	{
		print(philo, " is thinking\n");
		ft_usleep(philo->info->time_eat);
	}
}

void	philo_finish(t_philo *philo)
{
	mutex_handle(&philo->info->m_stop, LOCK);
	if (++philo->info->philo_eat == philo->info->num_philo)
	{
		mutex_handle(&philo->info->m_stop, UNLOCK);
		is_dead(philo, 2);
	}
	mutex_handle(&philo->info->m_stop, UNLOCK);
}

void	*philo_life(void *phi)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)phi;
	if (philo->info->num_philo == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while (!is_dead(philo, 0))
	{
		pthread_create(&t, NULL, check_death, phi);
		synchronized(philo);
		take_fork(philo);
		eating(philo);
		pthread_detach(t);
		if (philo->m_count == philo->info->num_eat)
		{
			philo_finish(philo);
			return (NULL);
		}
	}
	return (NULL);
}
