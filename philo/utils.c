/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:09:40 by cgaratej          #+#    #+#             */
/*   Updated: 2024/09/27 14:26:40 by cgaratej         ###   ########.fr       */
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
	if (!philo->info->stop && time >= 0 && time <= INT_MAX)
		printf("%lld %d %s", timestamp() - philo->info->t_start, philo->id, str);
	pthread_mutex_unlock(&(philo->info->print));
}

int	mutex_error_check(int status)
{
	if (status == INIT)
		printf("Problem initializing the mutex.\n");
	if (status == LOCK)
		printf("Problem locking the mutex.\n");
	if (status == UNLOCK)
		printf("Problem unlocking the mutex.\n");
	if (status == DESTROY)
		printf("Problem destroying the mutex.\n");
	return (1);
}

int	mutex_handle(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			return (mutex_error_check(INIT));
	}
	else if (opcode == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			return (mutex_error_check(LOCK));
	}
	else if (opcode == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
			return (mutex_error_check(UNLOCK));
	}
	else if (opcode == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			return (mutex_error_check(DESTROY));
	}
	return (0);
}
