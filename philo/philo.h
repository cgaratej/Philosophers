/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:54:45 by cgaratej          #+#    #+#             */
/*   Updated: 2024/09/10 17:13:50 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				m_count;
	int				is_eating;
	struct t_info	*info;
	long int		last_eat;
	/*pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;*/
}	t_philo;

typedef struct s_info
{

	int				philo_eat;
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	int				stop;
	long int		t_start;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	dead;
}	t_info;


int			ft_atoi(char *num);
int			var_init(t_info *data, char **argv);
int			init_philos(t_info *data);
long long	timestamp(void);

#endif