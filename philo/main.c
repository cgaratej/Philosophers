/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:01:06 by cgaratej          #+#    #+#             */
/*   Updated: 2024/10/22 16:27:56 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_data(t_info *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		mutex_handle(&data->philo[i].fork_l, DESTROY);
	}
	mutex_handle(&data->print, DESTROY);
	mutex_handle(&data->m_eat, DESTROY);
	mutex_handle(&data->m_stop, DESTROY);
	mutex_handle(&data->dead, DESTROY);
	free(data->philo);
}

static int	check_syntax(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (!argv[i][j])
			return (1);
		if (argv[i][j] == '+' || argv[i][j] == '-')
		{
			if (!(argv[i][j + 1] >= '0' && argv[i][j + 1] <= '9'))
				return (printf("Must be numbers.\n"), 1);
			j++;
		}
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (printf("Must be numbers.\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_args(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_atoi(argv[1]) < 0)
			return (printf("There must be at least 1 philosopher.\n"), 1);
		if (ft_atoi(argv[2]) < 1)
			return (printf("Time_to_die must be at least 1.\n"), 1);
		if (ft_atoi(argv[3]) < 1)
			return (printf("Time_to_eat must be at least 1.\n"), 1);
		if (ft_atoi(argv[4]) < 1)
			return (printf("Time_to_sleep must be at least 1.\n"), 1);
		if (argc == 6 && ft_atoi(argv[5]) < 1)
			return (printf("Number_of_times_each_philosopher_must_eat "
					"must be at least 1.\n"), 1);
	}
	else
	{
		return (printf("[number_of_philosophers] [time_to_die] [time_to_eat] "
				"[time_to_sleep]\n"
				"Optional [number_of_times_each_philosopher_must_eat]\n"), 1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	data;

	if (check_syntax(argv) | check_args(argc, argv))
		return (1);
	if (var_init(&data, argv) == 1)
	{
		free(data.philo);
		return (1);
	}
	printf("---------\n");
	init_philos(&data);
	pthread_join(data.t, NULL);
	free_data(&data);
}
