/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubov <lubov@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 00:23:06 by lubov             #+#    #+#             */
/*   Updated: 2022/02/04 00:23:06 by lubov            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				philo_id;
	int				die;
	long			last_eat;
	char			f_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_arg	*args;
}					t_philo;

typedef struct s_arg
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_eat;
	pthread_t		*thread_philo;
	pthread_mutex_t	lock_pr;
	pthread_mutex_t	*forks;
	t_philo			*data_philos;
	long			start;
}					t_arg;

int		ft_atoi(const char *str);
int		ft_isnumb(char *s);
void	init_thread(t_arg *args);
void	sleep_think(t_philo *philo);
void	eating(t_philo *philo);
long	get_time(void);
void	free_all(t_arg *args, int type);
void	*philo_process(void *data);
void	check_philo(t_arg *args);
void	ft_malloc(t_arg *args);
void	init_philo(t_arg *args);
#endif