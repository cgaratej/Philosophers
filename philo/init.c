/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:26:36 by cgaratej          #+#    #+#             */
/*   Updated: 2024/09/23 17:53:52 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_info *data)
{
	int	i;

	data->t_start = timestamp();
	i = -1;
	while (++i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = timestamp();
		data->philo[i].info = data;
		data->philo[i].m_count = 0;
		pthread_mutex_init(&(data->philo[i].fork_l), NULL);
		if (i == data->num_philo - 1)
			data->philo[i].fork_r = &data->philo[0].fork_l;
		else
			data->philo[i].fork_r = &data->philo[i + 1].fork_l;
	}
	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, \
				&philo_life, &(data->philo[i])) != 0)
			return (-1);
	}
	if (checke_deat(data))
		///printf("hol1a\n");
		return (1);
	i = -1;
	while (++i < data->num_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
	return (0);
}

int var_init(t_info *data, char **argv)
{
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	data->stop = 0;
	data->num_philo = ft_atoi(argv[1]);
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (data->philo == NULL)
		return (2);
	data->philo_eat = 0;
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->dead = 0;
	if (argv[5])
		data->num_eat = ft_atoi(argv[5]);
	else
		data->num_eat = 0;
	return (0);
}
