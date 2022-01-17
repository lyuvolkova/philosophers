#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_arg
{
    int number_of_philosophers;
    int  time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;

}t_arg;

typedef struct s_philo
{
    int philo_id;
    int  time_to_die;
    int time_to_eat;
    int time_to_sleep;



}t_philo;

#endif