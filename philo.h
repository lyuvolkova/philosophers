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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct s_arg
{
	int number_of_philo;
	int  time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_eat;
	pthread_mutex_t *forks;
	t_philo			*data_philo;

}t_arg; 

typedef struct s_philo
{
	int philo_id;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;

}t_philo;

int	ft_atoi(const char *str);
int ft_isnumb(char *s);

#endif