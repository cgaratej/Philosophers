/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:09:40 by cgaratej          #+#    #+#             */
/*   Updated: 2024/09/12 16:05:05 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *num)
{
	int	flag;
	int	i;
	int	result;

	flag = 1;
	i = 0;
	result = 0;
	while ((num[i] >= 9 && num[i] <= 13) || num[i] == 32)
		i++;
	if (num[i] == '+' || num[i] == '-')
	{
		if (num[i] == '-')
			flag *= -1;
		i++;
	}
	while (num[i] && num[i] >= '0' && num[i] <= '9')
	{
		result = ((result * 10) + (num[i] - '0'));
		i++;
	}
	return (result * flag);
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	is_dead(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->info->dead);
	if (flag)
		philo->info->stop = 1;
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->dead);
	return (0);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}

void	print(t_philo *philo, char *str)
{
	long int	time;

	pthread_mutex_lock(&(philo->info->print));
	time = timestamp() - philo->info->t_start;
	if (!philo->info->stop && time >= 0 \
			&& time <= INT_MAX && !is_dead(philo, 0))
		printf("%lld %d %s", timestamp() - philo->info->t_start, philo->id, str);
	pthread_mutex_unlock(&(philo->info->print));
}
