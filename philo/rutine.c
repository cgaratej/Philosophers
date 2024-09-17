/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:41:04 by cgaratej          #+#    #+#             */
/*   Updated: 2024/09/17 09:55:42 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*checke_deat(void *phi)
{
	t_philo *philo;

	philo = (t_philo *)phi;
	ft_usleep(philo->info->time_die + 1);
	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_stop);
	if (!is_dead(philo, 0) && timestamp() - \
			philo->last_eat >= (long)(philo->info->time_die))
	{
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_stop);
		print(philo, " died\n");
		is_dead(philo, 1);
	}
	pthread_mutex_unlock(&philo->info->m_eat);
	pthread_mutex_unlock(&philo->info->m_stop);
	return (NULL);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l);
	print(philo, " has taken a fork\n");
	/*if (philo->info->num_philo == 1)
	{
		ft_usleep(philo->info->time_die * 2);
		return ;
	}*/
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
	print(philo, " is thinking\n");
}

void	*philo_life(void *phi)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)phi;

	while (!is_dead(philo, 0))
	{
		pthread_create(&t, NULL, checke_deat, phi);
		take_fork(philo);
		eating(philo);
		pthread_detach(t);
		//if ()
	}
	return (NULL);
}