/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgrodd <qgrodd@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 23:30:54 by lubov             #+#    #+#             */
/*   Updated: 2022/02/08 19:14:12 by qgrodd           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int				philo_id;
	long			last_eat;
	char			f_eat;
	pid_t			pid;
	pthread_t		check;
	struct s_arg	*args;
}					t_philo;

typedef struct s_arg
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_eat;
	int				die;
	sem_t			*block_eat;
	sem_t			*lock_pr;
	sem_t			*forks;
	sem_t			*end;
	t_philo			*data_philos;
	long			start;
}					t_arg;

int		ft_atoi(const char *str);
int		ft_isnumb(char *s);
int		parent(t_philo *philo);
int		check_print(t_philo *philo);
long	get_time(void);
void	*check(void *data);
void	init_philo(t_arg *args);
void	free_all(t_arg *args, t_philo *philo);
void	eating(t_philo *philo, t_arg *args);
void	sleep_think(t_philo *philo, t_arg *args);
void	philo_process(t_philo *philo, t_arg *args);
void	free_all(t_arg *args, t_philo *philo);

#endif