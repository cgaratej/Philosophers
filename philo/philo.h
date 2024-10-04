/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:54:45 by cgaratej          #+#    #+#             */
/*   Updated: 2024/10/04 18:58:44 by cgaratej         ###   ########.fr       */
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
# include <limits.h>

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY
}	t_opcode;

typedef struct s_info	t_info;

typedef struct s_philo
{
	int				id;
	int				m_count;
	int				is_eating;
	pthread_t		thread;
	t_info			*info;
	long int		last_eat;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;
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
	pthread_t		t;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	dead;
}	t_info;

int			ft_atoi(char *num);
int			var_init(t_info *data, char **argv);
int			init_philos(t_info *data);
long long	timestamp(void);
void		ft_usleep(int ms, t_info *info);
void		*philo_life(void *phi);
void		print(t_philo *philo, char *str, int is_deat);
int			is_dead(t_info *info, int nb);
void		*check_death(void *phi);
int			mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
#endif