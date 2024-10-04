/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:26:36 by cgaratej          #+#    #+#             */
/*   Updated: 2024/10/04 19:02:29 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_pthreads(t_info *data)
{
	int	i;

	i = -1;
	data->t_start = timestamp();
	while (++i < data->num_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, \
				&philo_life, &(data->philo[i])) != 0)
			return (-1);
	}
	pthread_create(&data->t, NULL, check_death, data);
	i = -1;
	while (++i < data->num_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
	return (0);
}

int	init_philos(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = timestamp();
		data->philo[i].info = data;
		data->philo[i].m_count = 0;
		mutex_handle(&(data->philo[i].fork_l), INIT);
		if (i == data->num_philo - 1)
			data->philo[i].fork_r = &data->philo[0].fork_l;
		else
			data->philo[i].fork_r = &data->philo[i + 1].fork_l;
	}
	if (create_pthreads(data))
		return (-1);
	return (0);
}

int	var_init(t_info *data, char **argv)
{
	mutex_handle(&data->print, INIT);
	mutex_handle(&data->m_eat, INIT);
	mutex_handle(&data->m_stop, INIT);
	mutex_handle(&data->dead, INIT);
	data->stop = 0;
	data->num_philo = ft_atoi(argv[1]);
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (data->philo == NULL)
		return (2);
	data->philo_eat = 0;
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->num_eat = ft_atoi(argv[5]);
	else
		data->num_eat = 0;
	return (0);
}
