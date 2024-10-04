/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:09:40 by cgaratej          #+#    #+#             */
/*   Updated: 2024/10/04 19:07:24 by cgaratej         ###   ########.fr       */
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

void	ft_usleep(int ms, t_info *info)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms && !is_dead(info, 0))
		usleep(500);
}

void	print(t_philo *philo, char *str, int is_deat)
{
	long int	time;

	mutex_handle(&(philo->info->print), LOCK);
	time = timestamp() - philo->info->t_start;
	if (time >= 0 && time <= INT_MAX && (is_deat || !is_dead(philo->info, 0)))
		printf("%lld %d %s", timestamp() - philo->info->t_start, \
				philo->id, str);
	mutex_handle(&(philo->info->print), UNLOCK);
}
